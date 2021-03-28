#include <filesystem>
#include <iostream>

#include "TwitterSearch.hpp"
#include "FileVault.hpp"

int main() {
	std::cout << "Chirp Explorer - Search Twitter\n";

	auto pathToBearerFile = std::filesystem::temp_directory_path();
	pathToBearerFile /= "FindTheChirpsCred.txt";
	chirpexplorer::FileVault tokenVault(pathToBearerFile);

	auto const tweets = chirpexplorer::twitterSearch(tokenVault);
	for (auto const& tweet : tweets)
		std::cout << tweet << '\n';

	return 0;
}