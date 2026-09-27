#include "point.hpp"

#include <cmath>

Point::Point(int x, int y) : x_(x), y_(y) {
}

int Point::getX() const {
    return x_;
}

int Point::getY() const {
    return y_;
}

double Point::distanceTo(const Point& other) const {
    return std::hypot(static_cast<double>(x_) - other.x_, static_cast<double>(y_) - other.y_);
}
