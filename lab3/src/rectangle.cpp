#include "rectangle.hpp"

#include <cmath>

Rectangle::Rectangle(const Point& point1, const Point& point2, const Point& point3,
                     const Point& point4)
    : Figure(Vertices{point1, point2, point3, point4}) {
}

double Rectangle::getArea() const {
    const double width = std::hypot(vertex(1).x - vertex(0).x, vertex(1).y - vertex(0).y);
    const double height = std::hypot(vertex(3).x - vertex(0).x, vertex(3).y - vertex(0).y);
    return width * height;
}

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}
