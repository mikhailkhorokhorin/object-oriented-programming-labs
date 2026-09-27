#include <iostream>
#include <string>

#include "solution.hpp"

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << removeVowels(line) << '\n';
    }
    return 0;
}
