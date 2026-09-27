#pragma once

#include <cmath>
#include <cstddef>
#include <memory>

#include "figure.hpp"

template <Scalar T>
class Rhombus final : public Figure<T> {
public:
    static constexpr std::size_t VERTEX_COUNT = 4;

    Rhombus() : Figure<T>(VERTEX_COUNT) {}

    Rhombus(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
            const Point<T>& point4)
        : Figure<T>({point1, point2, point3, point4}) {}

    double getArea() const override {
        if (this->getSize() != VERTEX_COUNT) {
            return 0.0;
        }
        return distance(this->vertex(0), this->vertex(2)) *
               distance(this->vertex(1), this->vertex(3)) / 2.0;
    }

    std::unique_ptr<Figure<T>> clone() const override { return std::make_unique<Rhombus>(*this); }

private:
    static double distance(const Point<T>& lhs, const Point<T>& rhs) {
        return std::hypot(static_cast<double>(lhs.x) - static_cast<double>(rhs.x),
                          static_cast<double>(lhs.y) - static_cast<double>(rhs.y));
    }
};
