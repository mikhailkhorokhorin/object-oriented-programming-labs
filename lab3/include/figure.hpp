#pragma once

#include <memory>

#include "point.hpp"

class Figure {
   protected:
    Point* points_ = nullptr;
    size_t size_ = 0;

    virtual double getArea() const = 0;

   public:
    virtual ~Figure();

    virtual operator double() const;

    size_t getSize() const;
    const Point* getPoints() const;

    virtual Point getCenter() const = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    virtual bool operator==(const Figure& other) const = 0;
    virtual std::unique_ptr<Figure> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
    friend std::istream& operator>>(std::istream& is, Figure& figure);
};
