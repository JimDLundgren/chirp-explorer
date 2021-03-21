// REST API library
#define CPPHTTPLIB_OPENSSL_SUPPORT // Requires linking against libssl and libcrypto
#include <httplib.h>

// JSON parsing library
#include <nlohmann/json.hpp>

// Standard library
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Local library
#include "FileVault.hpp"
#include "Utils.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

int main() {
	std::cout << "Chirp Explorer - Search Twitter\n";

	auto pathToBearerFile = fs::temp_directory_path();
	pathToBearerFile /= "FindTheChirpsCred.txt";
	chirpexplorer::FileVault vault(pathToBearerFile);
	
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

	auto const query = chirpexplorer::getUserInput<std::string>("Enter search query");
	auto const maxResults = std::clamp(
		chirpexplorer::getUserInput<int>("How many search results do you want [10-100]"),
		10, 100);

	httplib::Client cli("https://api.twitter.com");
	cli.set_bearer_token_auth(bearerToken.c_str());
	httplib::Headers headers;

	httplib::Params params;
	params.emplace("query", query);
	params.emplace("max_results", std::to_string(maxResults));
	params.emplace("tweet.fields", "text");

	auto res = cli.Get("/2/tweets/search/recent", params, headers);

	if (res->status != 200) {
		std::cerr << "Request error: " << res.error() << '\n';
		return -1;
	}

	std::stringstream tweetsFoundRawJson(res->body);

	json tweets;
	tweetsFoundRawJson >> tweets;
	json tweetsData = tweets["data"];

	for (auto const& kv : tweetsData.items()) {
		json value = kv.value();
		std::cout << value["text"] << '\n';
	}

	return 0;
}