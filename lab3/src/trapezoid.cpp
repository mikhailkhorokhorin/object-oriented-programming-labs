#include "trapezoid.hpp"

Trapezoid::Trapezoid(const Point& point1, const Point& point2, const Point& point3,
                     const Point& point4)
    : Figure(Vertices{point1, point2, point3, point4}) {
}

double Trapezoid::getArea() const {
    return polygonArea();
}

std::unique_ptr<Figure> Trapezoid::clone() const {
    return std::make_unique<Trapezoid>(*this);
}
