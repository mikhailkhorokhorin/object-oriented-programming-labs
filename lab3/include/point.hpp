#pragma once

#include <iostream>

struct Point {
    double x{};
    double y{};

    bool operator==(const Point& other) const = default;
};

std::istream& operator>>(std::istream& is, Point& point);
std::ostream& operator<<(std::ostream& os, const Point& point);
