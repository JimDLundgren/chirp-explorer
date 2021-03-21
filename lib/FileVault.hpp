#pragma once

#include <filesystem>

#include "TokenVault.hpp"

namespace chirpexplorer {

class FileVault : public TokenVault {
	std::filesystem::path _tokenFile;

public:
	virtual std::pair<Token, bool> load() override;
	virtual bool store(Token token) override;

	FileVault(std::filesystem::path tokenFile);
};

}