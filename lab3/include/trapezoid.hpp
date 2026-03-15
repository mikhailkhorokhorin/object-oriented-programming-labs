#pragma once

#include <algorithm>
#include <cmath>

#include "figure.hpp"


class Trapezoid : public Figure {
   protected:
    double getArea() const override;

   public:
    Trapezoid();
    Trapezoid(const Point& point1, const Point& point2, const Point& point3, const Point& point4);
    Trapezoid(const Trapezoid& other);

    Point getCenter() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    bool operator==(const Trapezoid& other) const;
    bool operator==(const Figure& other) const override;

    std::unique_ptr<Figure> clone() const override;
};
