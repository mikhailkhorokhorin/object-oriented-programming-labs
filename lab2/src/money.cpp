#include "money.hpp"

void Money::allocateMemory(size_t size) {
    digits_ = new unsigned char[size];
    size_ = size;
}

void Money::deallocateMemory() {
    delete[] digits_;
    digits_ = nullptr;
    size_ = 0;
}

void Money::parseString(const std::string& amount) {
    size_t dot = amount.find('.');

    if (dot == std::string::npos)
        throw std::invalid_argument("Missing point in number.");

    std::string rubles = amount.substr(0, dot);
    std::string kopecks = amount.substr(dot + 1);

    if (kopecks.size() != 2)
        throw std::invalid_argument("Number must have exactly two kopecks digits.");

    std::string digits = rubles + kopecks;

    for (char c : digits)
        if (!std::isdigit(c))
            throw std::invalid_argument("Number must contain only digits.");

    size_t size = digits.size();

    deallocateMemory();
    allocateMemory(size);

    for (size_t i = 0; i < size; ++i)
        digits_[i] = digits[size - i - 1] - '0';
}

void Money::parseDouble(double amount) {
    if (amount < 0)
        throw std::invalid_argument("Number mast be positive.");

    unsigned long long number = static_cast<unsigned long long>(std::round(amount * 100));
    unsigned long long temp = number;

    size_t size = 0;
    do {
        ++size;
        temp /= 10;
    } while (temp > 0);

    deallocateMemory();
    allocateMemory(size);

    for (size_t i = 0; i < size; ++i) {
        digits_[i] = number % 10;
        number /= 10;
    }
}

Money::Money() : digits_(nullptr), size_(0) {
    allocateMemory(1);
    digits_[0] = 0;
}

Money::Money(const std::string& amount) : digits_(nullptr), size_(0) {
    parseString(amount);
}

Money::Money(double amount) : digits_(nullptr), size_(0) {
    parseDouble(amount);
}

Money::Money(const Money& other) : digits_(nullptr), size_(0) {
    allocateMemory(other.size_);
    for (size_t i = 0; i < other.size_; ++i)
        digits_[i] = other.digits_[i];
}

Money::Money(Money&& other) noexcept : digits_(other.digits_), size_(other.size_) {
    other.digits_ = nullptr;
    other.size_ = 0;
}

Money::~Money() {
    deallocateMemory();
}

Money Money::add(const Money& a, const Money& b) {
    size_t size = std::max(a.size_, b.size_) + 1;
    Money result;

    result.deallocateMemory();
    result.allocateMemory(size);

    unsigned carry = 0;

    for (size_t i = 0; i < size - 1; ++i) {
        unsigned value = carry;
        if (i < a.size_)
            value += a.digits_[i];
        if (i < b.size_)
            value += b.digits_[i];

        result.digits_[i] = value % 10;
        carry = value / 10;
    }

    result.digits_[size - 1] = carry;
    return result;
}

Money Money::subtract(const Money& a, const Money& b) {
    if (less(a, b))
        throw std::invalid_argument("Result cannot be negative.");

    Money result = a;
    unsigned carry = 0;

    for (size_t i = 0; i < result.size_; ++i) {
        int diff = result.digits_[i] - (i < b.size_ ? b.digits_[i] : 0) - carry;
        carry = diff < 0;
        result.digits_[i] = static_cast<unsigned char>(diff + (carry ? 10 : 0));
    }

    return result;
}

bool Money::equals(const Money& a, const Money& b) {
    if (a.size_ != b.size_)
        return false;
    for (size_t i = 0; i < a.size_; ++i)
        if (a.digits_[i] != b.digits_[i])
            return false;
    return true;
}

bool Money::notEquals(const Money& a, const Money& b) {
    return !equals(a, b);
}

bool Money::greater(const Money& a, const Money& b) {
    if (a.size_ != b.size_)
        return a.size_ > b.size_;

    for (size_t i = a.size_; i > 0; --i) {
        if (a.digits_[i - 1] != b.digits_[i - 1])
            return a.digits_[i - 1] > b.digits_[i - 1];
    }

    return false;
}

bool Money::less(const Money& a, const Money& b) {
    return greater(b, a);
}

bool Money::greaterOrEqual(const Money& a, const Money& b) {
    return !less(a, b);
}

bool Money::lessOrEqual(const Money& a, const Money& b) {
    return !greater(a, b);
}

Money Money::copy(const Money& other) {
    Money result;
    result.deallocateMemory();
    result.allocateMemory(other.size_);

    for (size_t i = 0; i < other.size_; ++i)
        result.digits_[i] = other.digits_[i];

    return result;
}

void Money::print(char sep) const {
    std::cout << toString(sep) << std::endl;
}

size_t Money::getSize() const {
    return size_;
}

const unsigned char* Money::getDigits() const {
    return digits_;
}

std::string Money::toString(char sep) const {
    std::string result;

    if (size_ <= 2)
        result = "0";
    else
        for (int i = static_cast<int>(size_) - 1; i >= 2; --i)
            result += '0' + digits_[i];

    result += sep;
    result += '0' + (size_ >= 2 ? digits_[1] : 0);
    result += '0' + digits_[0];

    return result;
}

double Money::toDouble() const {
    double result = 0.0;
    double factor = 1.0;

    for (size_t i = 0; i < size_; ++i) {
        result += digits_[i] * factor;
        factor *= 10.0;
    }

    if (size_ >= 2)
        result /= 100.0;

    return result;
}
