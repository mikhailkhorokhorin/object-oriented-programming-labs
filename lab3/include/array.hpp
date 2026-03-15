#pragma once

#include "figure.hpp"

class Array {
   private:
    Figure** figures_;
    size_t size_;
    size_t capacity_;

    void resize(size_t capacity);

   public:
    explicit Array(size_t capacity = 2);

    Array(const Array& other);
    Array(Array&& other) noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    ~Array();

    void addFigure(Figure* figure);
    void removeFigure(size_t index);
    Figure* getFigure(size_t index) const;

    size_t getSize() const;
    size_t getCapacity() const;

    double getAllArea() const;
    void printFigures() const;

    Figure* operator[](size_t index) const;
};
