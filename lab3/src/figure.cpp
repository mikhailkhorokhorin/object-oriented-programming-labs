#include "figure.hpp"

#include <algorithm>
#include <cmath>
#include <typeinfo>

namespace {

constexpr double EPSILON = 1e-12;

double cross(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.y - rhs.x * lhs.y;
}

double signedDoubleArea(const Figure::Vertices& points) {
    double area = 0.0;
    for (std::size_t i = 0; i < points.size(); ++i) {
        area += cross(points[i], points[(i + 1) % points.size()]);
    }
    return area;
}

Figure::Vertices sorted(Figure::Vertices points) {
    std::ranges::sort(points, [](const Point& lhs, const Point& rhs) {
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    });
    return points;
}

}

Figure::Figure(const Vertices& points) : points_(points) {
}

Figure::operator double() const {
    return getArea();
}

std::size_t Figure::getSize() const {
    return points_.size();
}

const Figure::Vertices& Figure::getPoints() const {
    return points_;
}

Point Figure::getCenter() const {
    const double doubleArea = signedDoubleArea(points_);
    Point center;
    if (std::abs(doubleArea) < EPSILON) {
        for (const auto& point : points_) {
            center.x += point.x;
            center.y += point.y;
        }
        const auto count = static_cast<double>(points_.size());
        return Point{center.x / count, center.y / count};
    }
    for (std::size_t i = 0; i < points_.size(); ++i) {
        const Point& current = points_[i];
        const Point& next = points_[(i + 1) % points_.size()];
        const double factor = cross(current, next);
        center.x += (current.x + next.x) * factor;
        center.y += (current.y + next.y) * factor;
    }
    return Point{center.x / (3.0 * doubleArea), center.y / (3.0 * doubleArea)};
}

double Figure::polygonArea() const {
    return std::abs(signedDoubleArea(points_)) / 2.0;
}

void Figure::print(std::ostream& os) const {
    const char* separator = "";
    for (const auto& point : points_) {
        os << separator << point;
        separator = " ";
    }
}

void Figure::read(std::istream& is) {
    Vertices points;
    for (auto& point : points) {
        is >> point;
    }
    if (is) {
        points_ = points;
    }
}

bool Figure::operator==(const Figure& other) const {
    return typeid(*this) == typeid(other) && sorted(points_) == sorted(other.points_);
}

const Point& Figure::vertex(std::size_t index) const {
    return points_.at(index);
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.read(is);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.print(os);
    return os;
}
