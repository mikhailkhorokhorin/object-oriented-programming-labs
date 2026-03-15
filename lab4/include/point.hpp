#pragma once

#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
    T x{}, y{};

    Point() : x(0), y(0) {
    }
    Point(T x_, T y_) : x(x_), y(y_) {
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    friend std::istream& operator>>(std::istream& is, Point& point) {
        return is >> point.x >> point.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        return os << "(" << point.x << ", " << point.y << ")";
    }
};
