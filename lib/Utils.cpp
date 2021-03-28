#include <nlohmann/json.hpp>

#include <filesystem>
#include <sstream>

#include "Utils.hpp"

using json = nlohmann::json;

namespace chirpexplorer {

std::string getBearerToken(chirpexplorer::TokenVault& vault) 
{
	std::string bearerToken;
	
	auto storedToken = vault.load();
	if (storedToken.second) {
		bearerToken = storedToken.first;
	}
	else {
		bearerToken = chirpexplorer::getUserInput<std::string>("Enter the bearer token for your Twitter app to continue");
		if (!(vault.store(bearerToken))) {
			std::cerr << "Unable to persist bearer token for usage on subsequent runs.\n";
		}
	}

	return bearerToken;
}

HttpParams getTwitterSearchParamsFromUser()
{
	HttpParams params;

	auto const query = chirpexplorer::getUserInput<std::string>("Enter search query");
	params.emplace("query", query);

	auto const maxResults = std::clamp(
		chirpexplorer::getUserInput<int>("How many search results do you want [10-100]"),
		10, 100);
	params.emplace("max_results", std::to_string(maxResults));

	return params;
}

Tweets parseTweetSearchResult(std::string resultBody) 
{
	std::stringstream sstreamBody(resultBody);
	json tweetsBody;
	sstreamBody >> tweetsBody;

	Tweets tweetsFound;
	json tweetsData = tweetsBody["data"];

	for (auto const& kv : tweetsData.items()) {
		json value = kv.value();
		tweetsFound.push_back(value["text"]);
	}

	return tweetsFound;
}

}