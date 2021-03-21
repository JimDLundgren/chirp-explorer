#pragma once

#include <string>

namespace chirpexplorer {

template <typename T>
T getUserInput(std::string msgAskingForInput) {
	std::cout << msgAskingForInput << ": ";
	T input;
	std::cin >> input;
	return input;
}

}