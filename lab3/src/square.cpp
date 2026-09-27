#include "square.hpp"

#include <cmath>

Square::Square(const Point& point1, const Point& point2, const Point& point3, const Point& point4)
    : Figure(Vertices{point1, point2, point3, point4}) {
}

double Square::getArea() const {
    const double side = std::hypot(vertex(1).x - vertex(0).x, vertex(1).y - vertex(0).y);
    return side * side;
}

std::unique_ptr<Figure> Square::clone() const {
    return std::make_unique<Square>(*this);
}
