#pragma once

#include <iostream>

struct Point {
    double x{}, y{};

    bool operator==(const Point& other) const;
};

std::istream& operator>>(std::istream& is, Point& point);
std::ostream& operator<<(std::ostream& os, const Point& point);
