#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

class Money {
   private:
    unsigned char* digits_;
    size_t size_;

    void allocateMemory(size_t size);
    void deallocateMemory();

    void parseString(const std::string& amount);
    void parseDouble(double amount);

   public:
    Money();

    explicit Money(const std::string& amount);
    explicit Money(double amount);

    Money(const Money& other);
    Money(Money&& other) noexcept;

    ~Money();

    static Money add(const Money&, const Money&);
    static Money subtract(const Money&, const Money&);

    static bool equals(const Money&, const Money&);
    static bool notEquals(const Money&, const Money&);
    static bool greater(const Money&, const Money&);
    static bool less(const Money&, const Money&);
    static bool greaterOrEqual(const Money&, const Money&);
    static bool lessOrEqual(const Money&, const Money&);

    static Money copy(const Money& other);
    void print(char sep = '.') const;
    size_t getSize() const;
    const unsigned char* getDigits() const;

    std::string toString(char sep = '.') const;
    double toDouble() const;
};
