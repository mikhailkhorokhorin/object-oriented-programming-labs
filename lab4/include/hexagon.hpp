#pragma once

#include <cstddef>
#include <memory>

#include "figure.hpp"

template <Scalar T>
class Hexagon final : public Figure<T> {
public:
    static constexpr std::size_t VERTEX_COUNT = 6;

    Hexagon() : Figure<T>(VERTEX_COUNT) {}

    Hexagon(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
            const Point<T>& point4, const Point<T>& point5, const Point<T>& point6)
        : Figure<T>({point1, point2, point3, point4, point5, point6}) {}

    std::unique_ptr<Figure<T>> clone() const override { return std::make_unique<Hexagon>(*this); }
};
