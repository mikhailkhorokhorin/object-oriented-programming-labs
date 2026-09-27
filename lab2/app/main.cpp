#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "money.hpp"

int main() {
    try {
        std::string lhsText;
        std::string rhsText;
        while (std::cin >> lhsText) {
            if (!(std::cin >> rhsText)) {
                throw std::invalid_argument("missing second amount after " + lhsText);
            }
            const Money lhs(lhsText);
            const Money rhs(rhsText);
            std::cout << lhs.toString() << " + " << rhs.toString() << " = "
                      << Money::add(lhs, rhs).toString() << '\n';
            if (Money::greaterOrEqual(lhs, rhs)) {
                std::cout << lhs.toString() << " - " << rhs.toString() << " = "
                          << Money::subtract(lhs, rhs).toString() << '\n';
            } else {
                std::cout << lhs.toString() << " < " << rhs.toString() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
