#pragma once

#include <cmath>
#include <iostream>
#include <sstream>

#include "figure.hpp"

template <Scalar T>
class Hexagon : public Figure<T> {
   public:
    Hexagon(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
            const Point<T>& point4, const Point<T>& point5, const Point<T>& point6) {
        this->size_ = 6;
        this->points_ = std::make_unique<Point<T>[]>(6);

        this->points_[0] = point1;
        this->points_[1] = point2;
        this->points_[2] = point3;
        this->points_[3] = point4;
        this->points_[4] = point5;
        this->points_[5] = point6;
    }

    Hexagon() = default;

    Hexagon(const Hexagon& other) {
        this->size_ = other.size_;
        this->points_ = std::make_unique<Point<T>[]>(this->size_);

        for (size_t i = 0; i < this->size_; ++i)
            this->points_[i] = other.points_[i];
    }

    Point<T> getCenter() const override {
        T cx = 0, cy = 0;
        for (size_t i = 0; i < this->size_; ++i) {
            cx += this->points_[i].x;
            cy += this->points_[i].y;
        }
        return Point<T>(cx / this->size_, cy / this->size_);
    }

    double getArea() const override {
        double area = 0.0;

        for (size_t i = 0; i < this->size_; ++i) {
            const Point<T>& p1 = this->points_[i];
            const Point<T>& p2 = this->points_[(i + 1) % this->size_];
            area += (p1.x * p2.y - p2.x * p1.y);
        }

        return std::abs(area) / 2.0;
    }

    void print(std::ostream& os) const override {
        for (size_t i = 0; i < this->size_; ++i)
            os << "(" << this->points_[i].x << "," << this->points_[i].y << ") ";
        os << "Area = " << getArea() << " ";
        os << "Center: (" << getCenter().x << "," << getCenter().y << ")" << std::endl;
    }

    void read(std::istream& is) override {
        this->size_ = 6;
        this->points_ = std::make_unique<Point<T>[]>(6);

        for (size_t i = 0; i < this->size_; ++i)
            is >> this->points_[i].x >> this->points_[i].y;
    }

    bool operator==(const Hexagon<T>& other) const {
        for (size_t i = 0; i < 6; ++i)
            if (!(this->points_[i] == other.points_[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Hexagon<T>* hexagon = dynamic_cast<const Hexagon<T>*>(&other);
        if (!hexagon)
            return false;
        return *this == *hexagon;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Hexagon<T>>(*this);
    }
};
