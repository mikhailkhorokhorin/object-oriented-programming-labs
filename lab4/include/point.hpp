#pragma once

#include <iostream>
#include <type_traits>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
    T x{};
    T y{};

    bool operator==(const Point& other) const = default;

    friend std::istream& operator>>(std::istream& is, Point& point) {
        return is >> point.x >> point.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        return os << "(" << point.x << ", " << point.y << ")";
    }
};
