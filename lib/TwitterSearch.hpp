#pragma once

#include <string>
#include <vector>

#include "TokenVault.hpp"

namespace chirpexplorer {

using Tweets = std::vector<std::string>;

Tweets twitterSearch(TokenVault& vault);

}