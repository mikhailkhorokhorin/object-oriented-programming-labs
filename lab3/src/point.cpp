#include "point.hpp"

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

std::istream& operator>>(std::istream& is, Point& point) {
    return is >> point.x >> point.y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    return os << "(" << point.x << ", " << point.y << ")";
}
