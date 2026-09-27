#pragma once

#include <cstddef>
#include <iostream>
#include <memory>

#include "figure.hpp"

class Array {
public:
    explicit Array(std::size_t capacity = 2);

    Array(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    ~Array() = default;

    void addFigure(std::unique_ptr<Figure> figure);
    void removeFigure(std::size_t index);
    Figure* getFigure(std::size_t index) const;

    std::size_t getSize() const;
    std::size_t getCapacity() const;

    double getAllArea() const;
    void printFigures(std::ostream& os = std::cout) const;

    Figure* operator[](std::size_t index) const;

private:
    std::unique_ptr<std::unique_ptr<Figure>[]> figures_;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void resize(std::size_t capacity);
    void swap(Array& other) noexcept;
};
