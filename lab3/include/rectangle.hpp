#pragma once

#include <memory>

#include "figure.hpp"

class Rectangle final : public Figure {
public:
    Rectangle() = default;
    Rectangle(const Point& point1, const Point& point2, const Point& point3, const Point& point4);

    std::unique_ptr<Figure> clone() const override;

protected:
    double getArea() const override;
};
