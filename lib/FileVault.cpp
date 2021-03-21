#include <fstream>
#include <iostream>

#include "FileVault.hpp"
#include "Utils.hpp"

namespace fs = std::filesystem;

namespace chirpexplorer {

std::pair<Token, bool> FileVault::load()
{
	Token token;

	if (fs::exists(_tokenFile)) {
		std::ifstream ifs(_tokenFile);
		if (ifs.is_open()) {
			std::getline(ifs, token);
			return { token, true };
		}
	}
	
	return { token, false };
}

bool FileVault::store(Token token)
{
	std::ofstream ofs(_tokenFile);

	if (ofs.is_open()) {
		ofs << token;
		return true;
	}
	else {
		return false;
	}
}

FileVault::FileVault(fs::path tokenFile)
	: _tokenFile(tokenFile)
{
}

}