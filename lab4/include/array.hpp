#pragma once

#include <iostream>
#include <memory>

#include "figure.hpp"

template <Scalar T>
class Array {
   private:
    std::shared_ptr<Figure<T>>* figures_;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        auto* figures = new std::shared_ptr<Figure<T>>[new_capacity];
        for (size_t i = 0; i < size_; ++i)
            figures[i] = figures_[i];

        delete[] figures_;
        figures_ = figures;
        capacity_ = new_capacity;
    }

   public:
    explicit Array(size_t capacity = 2) : size_(0), capacity_(capacity) {
        figures_ = new std::shared_ptr<Figure<T>>[capacity_];
    }

    ~Array() {
        delete[] figures_;
    }

    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        figures_ = new std::shared_ptr<Figure<T>>[capacity_];

        for (size_t i = 0; i < size_; ++i)
            figures_[i] = other.figures_[i]->clone();
    }

    Array(Array&& other) noexcept
        : figures_(other.figures_), size_(other.size_), capacity_(other.capacity_) {
        other.figures_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Array& operator=(Array other) {
        std::swap(figures_, other.figures_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        std::swap(figures_, other.figures_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        return *this;
    }

    void addFigure(const std::shared_ptr<Figure<T>>& figure) {
        if (size_ >= capacity_)
            resize(capacity_ * 2);

        figures_[size_++] = figure;
    }

    void removeFigure(size_t index) {
        if (index >= size_)
            return;

        for (size_t i = index; i < size_ - 1; ++i)
            figures_[i] = figures_[i + 1];

        --size_;
    }

    std::shared_ptr<Figure<T>> getFigure(size_t index) const {
        if (index >= size_)
            return nullptr;

        return figures_[index];
    }

    size_t getSize() const {
        return size_;
    }
    size_t getCapacity() const {
        return capacity_;
    }

    double getAllArea() const {
        double sum = 0;

        for (size_t i = 0; i < size_; ++i)
            sum += static_cast<double>(*figures_[i]);

        return sum;
    }

    void printFigures() const {
        for (size_t i = 0; i < size_; ++i) {
            std::cout << "Figure " << i + 1 << ": ";
            figures_[i]->print(std::cout);

            auto center = figures_[i]->getCenter();
            std::cout << "Center: (" << center.x << ", " << center.y << ") ";
            std::cout << "Area: " << static_cast<double>(*figures_[i]) << std::endl;
        }
    }

    std::shared_ptr<Figure<T>> operator[](size_t index) const {
        if (index >= size_)
            return nullptr;
        return figures_[index];
    }
};
