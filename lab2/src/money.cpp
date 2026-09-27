#include "money.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <ranges>
#include <stdexcept>

namespace {

constexpr unsigned BASE = 10;
constexpr double KOPECKS_PER_RUBLE = 100.0;
constexpr double MAX_AMOUNT = 1e15;

}

Money::Money() : digits_{0} {
}

Money::Money(const std::string& amount) {
    const std::size_t dot = amount.find('.');
    if (dot == std::string::npos) {
        throw std::invalid_argument("Missing point in number.");
    }
    const std::string kopecks = amount.substr(dot + 1);
    if (kopecks.size() != 2) {
        throw std::invalid_argument("Number must have exactly two kopecks digits.");
    }
    const std::string digits = amount.substr(0, dot) + kopecks;
    if (!std::ranges::all_of(
            digits, [](char c) { return std::isdigit(static_cast<unsigned char>(c)) != 0; })) {
        throw std::invalid_argument("Number must contain only digits.");
    }
    digits_.reserve(digits.size());
    for (const char c : std::views::reverse(digits)) {
        digits_.push_back(static_cast<unsigned char>(c - '0'));
    }
    normalize();
}

Money::Money(double amount) {
    if (!std::isfinite(amount) || amount < 0) {
        throw std::invalid_argument("Number must be a finite non-negative value.");
    }
    if (amount >= MAX_AMOUNT) {
        throw std::out_of_range("Number is too large.");
    }
    auto number = static_cast<unsigned long long>(std::llround(amount * KOPECKS_PER_RUBLE));
    do {
        digits_.push_back(static_cast<unsigned char>(number % BASE));
        number /= BASE;
    } while (number > 0);
}

void Money::normalize() {
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
    }
    if (digits_.empty()) {
        digits_.push_back(0);
    }
}

Money Money::add(const Money& lhs, const Money& rhs) {
    const std::size_t size = std::max(lhs.digits_.size(), rhs.digits_.size());
    Money result;
    result.digits_.assign(size + 1, 0);
    unsigned carry = 0;
    for (std::size_t i = 0; i < size; ++i) {
        unsigned value = carry;
        if (i < lhs.digits_.size()) {
            value += lhs.digits_[i];
        }
        if (i < rhs.digits_.size()) {
            value += rhs.digits_[i];
        }
        result.digits_[i] = static_cast<unsigned char>(value % BASE);
        carry = value / BASE;
    }
    result.digits_[size] = static_cast<unsigned char>(carry);
    result.normalize();
    return result;
}

Money Money::subtract(const Money& lhs, const Money& rhs) {
    if (less(lhs, rhs)) {
        throw std::invalid_argument("Result cannot be negative.");
    }
    Money result = lhs;
    int borrow = 0;
    for (std::size_t i = 0; i < result.digits_.size(); ++i) {
        const int subtrahend = i < rhs.digits_.size() ? rhs.digits_[i] : 0;
        int diff = result.digits_[i] - subtrahend - borrow;
        borrow = diff < 0 ? 1 : 0;
        if (borrow != 0) {
            diff += static_cast<int>(BASE);
        }
        result.digits_[i] = static_cast<unsigned char>(diff);
    }
    result.normalize();
    return result;
}

bool Money::equals(const Money& lhs, const Money& rhs) {
    return lhs.digits_ == rhs.digits_;
}

bool Money::notEquals(const Money& lhs, const Money& rhs) {
    return !equals(lhs, rhs);
}

bool Money::greater(const Money& lhs, const Money& rhs) {
    if (lhs.digits_.size() != rhs.digits_.size()) {
        return lhs.digits_.size() > rhs.digits_.size();
    }
    return std::ranges::lexicographical_compare(std::views::reverse(rhs.digits_),
                                                std::views::reverse(lhs.digits_));
}

bool Money::less(const Money& lhs, const Money& rhs) {
    return greater(rhs, lhs);
}

bool Money::greaterOrEqual(const Money& lhs, const Money& rhs) {
    return !less(lhs, rhs);
}

bool Money::lessOrEqual(const Money& lhs, const Money& rhs) {
    return !greater(lhs, rhs);
}

void Money::print(std::ostream& os, char sep) const {
    os << toString(sep) << '\n';
}

std::size_t Money::getSize() const {
    return digits_.size();
}

const std::vector<unsigned char>& Money::getDigits() const {
    return digits_;
}

std::string Money::toString(char sep) const {
    std::string result;
    if (digits_.size() <= 2) {
        result = "0";
    } else {
        for (std::size_t i = digits_.size(); i > 2; --i) {
            result += static_cast<char>('0' + digits_[i - 1]);
        }
    }
    result += sep;
    result += static_cast<char>('0' + (digits_.size() >= 2 ? digits_[1] : 0));
    result += static_cast<char>('0' + digits_[0]);
    return result;
}

double Money::toDouble() const {
    double result = 0.0;
    for (std::size_t i = digits_.size(); i > 0; --i) {
        result = result * BASE + digits_[i - 1];
    }
    return result / KOPECKS_PER_RUBLE;
}
