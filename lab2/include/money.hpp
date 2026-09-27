#pragma once

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

class Money {
public:
    Money();
    explicit Money(const std::string& amount);
    explicit Money(double amount);

    static Money add(const Money& lhs, const Money& rhs);
    static Money subtract(const Money& lhs, const Money& rhs);

    static bool equals(const Money& lhs, const Money& rhs);
    static bool notEquals(const Money& lhs, const Money& rhs);
    static bool greater(const Money& lhs, const Money& rhs);
    static bool less(const Money& lhs, const Money& rhs);
    static bool greaterOrEqual(const Money& lhs, const Money& rhs);
    static bool lessOrEqual(const Money& lhs, const Money& rhs);

    void print(std::ostream& os = std::cout, char sep = '.') const;
    std::size_t getSize() const;
    const std::vector<unsigned char>& getDigits() const;

    std::string toString(char sep = '.') const;
    double toDouble() const;

private:
    std::vector<unsigned char> digits_;

    void normalize();
};
