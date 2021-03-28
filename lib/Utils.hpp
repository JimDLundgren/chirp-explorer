#pragma once

#include <iostream>
#include <map>
#include <string>

#include "TwitterSearch.hpp"
#include "TokenVault.hpp"

namespace chirpexplorer {

using HttpParams = std::multimap<std::string, std::string>;

template <typename T>
T getUserInput(std::string msgAskingForInput) {
	std::cout << msgAskingForInput << ": ";
	T input;
	std::cin >> input;
	return input;
}

std::string getBearerToken(chirpexplorer::TokenVault& vault);
HttpParams getTwitterSearchParamsFromUser();
Tweets parseTweetSearchResult(std::string resultBody);

}