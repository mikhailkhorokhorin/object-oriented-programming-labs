#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <utility>

#include "point.hpp"

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    explicit operator double() const { return getArea(); }

    virtual double getArea() const { return std::abs(signedDoubleArea()) / 2.0; }

    std::size_t getSize() const { return size_; }

    const Point<T>* getPoints() const { return points_.get(); }

    Point<double> getCenter() const {
        if (size_ == 0) {
            return Point<double>{};
        }
        const double doubleArea = signedDoubleArea();
        if (std::abs(doubleArea) < EPSILON) {
            return vertexMean();
        }
        double sumX = 0.0;
        double sumY = 0.0;
        for (std::size_t i = 0; i < size_; ++i) {
            const Point<double> current = toDouble(points_[i]);
            const Point<double> next = toDouble(points_[(i + 1) % size_]);
            const double factor = cross(current, next);
            sumX += (current.x + next.x) * factor;
            sumY += (current.y + next.y) * factor;
        }
        return Point<double>{sumX / (3.0 * doubleArea), sumY / (3.0 * doubleArea)};
    }

    void print(std::ostream& os) const {
        for (std::size_t i = 0; i < size_; ++i) {
            os << (i == 0 ? "" : " ") << points_[i];
        }
    }

    void read(std::istream& is) {
        auto points = std::make_unique<Point<T>[]>(size_);
        for (std::size_t i = 0; i < size_; ++i) {
            is >> points[i];
        }
        if (is) {
            points_ = std::move(points);
        }
    }

    bool operator==(const Figure& other) const {
        return typeid(*this) == typeid(other) && size_ == other.size_ &&
               std::equal(points_.get(), points_.get() + size_, other.points_.get());
    }

    virtual std::unique_ptr<Figure> clone() const = 0;

    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        figure.read(is);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        figure.print(os);
        return os;
    }

protected:
    explicit Figure(std::size_t size) : points_(std::make_unique<Point<T>[]>(size)), size_(size) {}

    Figure(std::initializer_list<Point<T>> points) : Figure(points.size()) {
        std::copy(points.begin(), points.end(), points_.get());
    }

    Figure(const Figure& other) : Figure(other.size_) {
        std::copy(other.points_.get(), other.points_.get() + size_, points_.get());
    }

    Figure(Figure&& other) noexcept
        : points_(std::move(other.points_)), size_(std::exchange(other.size_, 0)) {}

    Figure& operator=(const Figure& other) {
        if (this != &other) {
            auto points = std::make_unique<Point<T>[]>(other.size_);
            std::copy(other.points_.get(), other.points_.get() + other.size_, points.get());
            points_ = std::move(points);
            size_ = other.size_;
        }
        return *this;
    }

    Figure& operator=(Figure&& other) noexcept {
        if (this != &other) {
            points_ = std::move(other.points_);
            size_ = std::exchange(other.size_, 0);
        }
        return *this;
    }

    const Point<T>& vertex(std::size_t index) const { return points_[index]; }

private:
    static constexpr double EPSILON = 1e-12;

    std::unique_ptr<Point<T>[]> points_;
    std::size_t size_ = 0;

    static Point<double> toDouble(const Point<T>& point) {
        return Point<double>{static_cast<double>(point.x), static_cast<double>(point.y)};
    }

    static double cross(const Point<double>& lhs, const Point<double>& rhs) {
        return lhs.x * rhs.y - rhs.x * lhs.y;
    }

    double signedDoubleArea() const {
        double area = 0.0;
        for (std::size_t i = 0; i < size_; ++i) {
            area += cross(toDouble(points_[i]), toDouble(points_[(i + 1) % size_]));
        }
        return area;
    }

    Point<double> vertexMean() const {
        Point<double> sum;
        for (std::size_t i = 0; i < size_; ++i) {
            sum.x += static_cast<double>(points_[i].x);
            sum.y += static_cast<double>(points_[i].y);
        }
        const auto count = static_cast<double>(size_);
        return Point<double>{sum.x / count, sum.y / count};
    }
};
