#pragma once

#include <algorithm>
#include <cmath>

#include "figure.hpp"


class Rectangle : public Figure {
   protected:
    double getArea() const override;

   public:
    Rectangle();
    Rectangle(const Point& point1, const Point& point2, const Point& point3, const Point& point4);
    Rectangle(const Rectangle& other);

    Point getCenter() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    bool operator==(const Rectangle& other) const;
    bool operator==(const Figure& other) const override;

    std::unique_ptr<Figure> clone() const override;
};
