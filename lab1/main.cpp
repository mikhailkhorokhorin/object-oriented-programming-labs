#include "solution.hpp"

int main() {
    std::string input;

    std::cout << "Enter a string: ";
    getline(std::cin, input);

    std::string result = removeVowels(input);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
