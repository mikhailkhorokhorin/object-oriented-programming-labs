#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

#include "figure.hpp"

template <Scalar T>
class Array {
public:
    using FigurePtr = std::shared_ptr<Figure<T>>;

    explicit Array(std::size_t capacity = 2)
        : figures_(std::make_unique<FigurePtr[]>(capacity)), capacity_(capacity) {}

    Array(const Array& other)
        : figures_(std::make_unique<FigurePtr[]>(other.capacity_)),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (std::size_t i = 0; i < size_; ++i) {
            figures_[i] = other.figures_[i]->clone();
        }
    }

    Array(Array&& other) noexcept
        : figures_(std::move(other.figures_)),
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)) {}

    Array& operator=(const Array& other) {
        if (this != &other) {
            Array copy(other);
            swap(copy);
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        Array moved(std::move(other));
        swap(moved);
        return *this;
    }

    ~Array() = default;

    void addFigure(FigurePtr figure) {
        if (!figure) {
            return;
        }
        if (size_ >= capacity_) {
            resize(std::max<std::size_t>(1, capacity_ * 2));
        }
        figures_[size_++] = std::move(figure);
    }

    void removeFigure(std::size_t index) {
        if (index >= size_) {
            return;
        }
        for (std::size_t i = index; i + 1 < size_; ++i) {
            figures_[i] = std::move(figures_[i + 1]);
        }
        figures_[--size_].reset();
    }

    FigurePtr getFigure(std::size_t index) const {
        return index < size_ ? figures_[index] : nullptr;
    }

    FigurePtr operator[](std::size_t index) const { return getFigure(index); }

    std::size_t getSize() const { return size_; }

    std::size_t getCapacity() const { return capacity_; }

    double getAllArea() const {
        double sum = 0;
        for (std::size_t i = 0; i < size_; ++i) {
            sum += figures_[i]->getArea();
        }
        return sum;
    }

    void printFigures(std::ostream& os = std::cout) const {
        for (std::size_t i = 0; i < size_; ++i) {
            os << "Figure " << i + 1 << ": " << *figures_[i]
               << " Center: " << figures_[i]->getCenter() << " Area: " << figures_[i]->getArea()
               << '\n';
        }
    }

private:
    std::unique_ptr<FigurePtr[]> figures_;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void swap(Array& other) noexcept {
        std::swap(figures_, other.figures_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void resize(std::size_t capacity) {
        auto figures = std::make_unique<FigurePtr[]>(capacity);
        for (std::size_t i = 0; i < size_; ++i) {
            figures[i] = std::move(figures_[i]);
        }
        figures_ = std::move(figures);
        capacity_ = capacity;
    }
};
