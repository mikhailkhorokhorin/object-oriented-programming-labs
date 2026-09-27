#pragma once

#include <array>
#include <cstddef>
#include <iostream>
#include <memory>

#include "point.hpp"

class Figure {
public:
    static constexpr std::size_t VERTEX_COUNT = 4;
    using Vertices = std::array<Point, VERTEX_COUNT>;

    virtual ~Figure() = default;

    explicit operator double() const;

    std::size_t getSize() const;
    const Vertices& getPoints() const;
    Point getCenter() const;

    void print(std::ostream& os) const;
    void read(std::istream& is);

    bool operator==(const Figure& other) const;

    virtual std::unique_ptr<Figure> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
    friend std::istream& operator>>(std::istream& is, Figure& figure);

protected:
    Figure() = default;
    explicit Figure(const Vertices& points);
    Figure(const Figure& other) = default;
    Figure(Figure&& other) noexcept = default;
    Figure& operator=(const Figure& other) = default;
    Figure& operator=(Figure&& other) noexcept = default;

    virtual double getArea() const = 0;
    double polygonArea() const;
    const Point& vertex(std::size_t index) const;

private:
    Vertices points_{};
};
