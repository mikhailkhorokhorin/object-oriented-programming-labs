#pragma once

#include <algorithm>
#include <cmath>

#include "figure.hpp"


class Square : public Figure {
   protected:
    double getArea() const override;

   public:
    Square();
    Square(const Point& point1, const Point& point2, const Point& point3, const Point& point4);
    Square(const Square& other);

    Point getCenter() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;

    bool operator==(const Square& other) const;
    bool operator==(const Figure& other) const override;

    std::unique_ptr<Figure> clone() const override;
};
