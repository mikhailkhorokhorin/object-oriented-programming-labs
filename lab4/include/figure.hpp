#pragma once

#include <iostream>
#include <memory>

#include "point.hpp"

template <Scalar T>
class Figure {
   protected:
    std::unique_ptr<Point<T>[]> points_;
    std::size_t size_ = 0;

    virtual double getArea() const = 0;

   public:
    virtual ~Figure() = default;

    virtual operator double() const {
        return getArea();
    }

    std::size_t getSize() const {
        return size_;
    }

    const Point<T>* getPoints() const {
        return points_.get();
    }

    virtual Point<T> getCenter() const = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    Figure& operator=(const Figure& other) {
        if (this == &other)
            return *this;

        size_ = other.size_;
        if (size_ > 0) {
            points_ = std::make_unique<Point<T>[]>(size_);
            for (size_t i = 0; i < size_; ++i)
                points_[i] = other.points_[i];
        } else {
            points_.reset();
        }

        return *this;
    }

    Figure& operator=(Figure&& other) noexcept {
        if (this == &other)
            return *this;

        points_ = std::move(other.points_);
        size_ = other.size_;
        other.size_ = 0;

        return *this;
    }

    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        return figure.read(is), is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        return figure.print(os), os;
    }
};
