#pragma once

#include <string>
#include <utility>

namespace chirpexplorer {

using Token = std::string;

class TokenVault {
public:
	virtual std::pair<Token, bool> load() = 0;
	virtual bool store(Token token) = 0;

	virtual ~TokenVault() = default;
};

}