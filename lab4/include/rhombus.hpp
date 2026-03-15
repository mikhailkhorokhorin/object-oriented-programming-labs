#pragma once

#include <cmath>
#include <iostream>

#include "figure.hpp"

template <Scalar T>
class Rhombus : public Figure<T> {
   private:
    static T distance(const Point<T>& a, const Point<T>& b) {
        T dx = a.x - b.x;
        T dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

   public:
    Rhombus(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
            const Point<T>& point4) {
        this->size_ = 4;
        this->points_ = std::make_unique<Point<T>[]>(4);

        this->points_[0] = point1;
        this->points_[1] = point2;
        this->points_[2] = point3;
        this->points_[3] = point4;
    }

    Rhombus() = default;

    Rhombus(const Rhombus& other) {
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
        T d1 = distance(this->points_[0], this->points_[2]);
        T d2 = distance(this->points_[1], this->points_[3]);

        return static_cast<double>(d1 * d2) / 2.0;
    }

    void print(std::ostream& os) const override {
        for (size_t i = 0; i < this->size_; ++i)
            os << "(" << this->points_[i].x << "," << this->points_[i].y << ") ";
        os << "Area = " << getArea() << " ";
        os << "Center: (" << getCenter().x << "," << getCenter().y << ")" << std::endl;
    }

    void read(std::istream& is) override {
        this->size_ = 4;
        this->points_ = std::make_unique<Point<T>[]>(4);

        for (size_t i = 0; i < this->size_; ++i)
            is >> this->points_[i].x >> this->points_[i].y;
    }

    bool operator==(const Rhombus<T>& other) const {
        for (size_t i = 0; i < 4; ++i)
            if (!(this->points_[i] == other.points_[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Rhombus<T>* rhombus = dynamic_cast<const Rhombus<T>*>(&other);
        if (!rhombus)
            return false;
        return *this == *rhombus;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhombus<T>>(*this);
    }
};
