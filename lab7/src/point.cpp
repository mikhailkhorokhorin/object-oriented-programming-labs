#include "point.hpp"

Point::Point(int x, int y) : x(x), y(y) {
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

double Point::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}
