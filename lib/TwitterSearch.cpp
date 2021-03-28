#define CPPHTTPLIB_OPENSSL_SUPPORT // Requires linking against libssl and libcrypto
#include <httplib.h>

#include <nlohmann/json.hpp>

#include <iostream>
#include <stdexcept>

#include "TwitterSearch.hpp"
#include "Utils.hpp"

namespace chirpexplorer {

Tweets twitterSearch(TokenVault& vault)
{
	auto const bearerToken = getBearerToken(vault);

	httplib::Client cli("https://api.twitter.com");
	cli.set_bearer_token_auth(bearerToken.c_str());
	httplib::Headers headers;

	httplib::Params params = getTwitterSearchParamsFromUser();
	params.emplace("tweet.fields", "text");

	auto res = cli.Get("/2/tweets/search/recent", params, headers);

	if (res->status != 200) {
		std::cerr << "Request error: " << res.error() << '\n';
		throw std::runtime_error("Request error: " + res.error() 
			+ std::string("\n Error status: ") + std::to_string(res->status));
	}

	auto tweets = parseTweetSearchResult(res->body);

	return tweets;
}

}