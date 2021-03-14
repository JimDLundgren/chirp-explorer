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

namespace fs = std::filesystem;
using json = nlohmann::json;

template <typename T>
T getUserInput(std::string msgAskingForInput) {
	std::cout << msgAskingForInput << ": ";
	T input;
	std::cin >> input;
	return input;
}

int main() {
	std::cout << "Chirp Explorer - Search Twitter\n";

	std::string bearerToken;
	auto pathToBearerFile = fs::temp_directory_path();
	pathToBearerFile /= "FindTheChirpsCred.txt";

	if (fs::exists(pathToBearerFile)) {
		std::ifstream ifs(pathToBearerFile);
		if (ifs.is_open()) {
			std::getline(ifs, bearerToken);
		}
		else {
			std::cerr << "Unable to read bearer token from file.\n";
		}
	}
	else {
		bearerToken = getUserInput<std::string>("Enter the bearer token for your Twitter app to continue");

		std::ofstream ofs(pathToBearerFile);
		if (ofs.is_open()) {
			ofs << bearerToken;
		}
		else {
			std::cerr << "Unable to write bearer token to file.\n";
		}
	}

	auto const query = getUserInput<std::string>("Enter search query");
	auto const maxResults = std::clamp(
		getUserInput<int>("How many search results do you want [10-100]"),
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