#include "array.hpp"

#include <algorithm>
#include <utility>

Array::Array(std::size_t capacity)
    : figures_(std::make_unique<std::unique_ptr<Figure>[]>(capacity)), capacity_(capacity) {
}

Array::Array(const Array& other)
    : figures_(std::make_unique<std::unique_ptr<Figure>[]>(other.capacity_)),
      size_(other.size_),
      capacity_(other.capacity_) {
    for (std::size_t i = 0; i < size_; ++i) {
        figures_[i] = other.figures_[i]->clone();
    }
}

Array::Array(Array&& other) noexcept
    : figures_(std::move(other.figures_)),
      size_(std::exchange(other.size_, 0)),
      capacity_(std::exchange(other.capacity_, 0)) {
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        Array copy(other);
        swap(copy);
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    Array moved(std::move(other));
    swap(moved);
    return *this;
}

void Array::swap(Array& other) noexcept {
    std::swap(figures_, other.figures_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void Array::resize(std::size_t capacity) {
    auto figures = std::make_unique<std::unique_ptr<Figure>[]>(capacity);
    for (std::size_t i = 0; i < size_; ++i) {
        figures[i] = std::move(figures_[i]);
    }
    figures_ = std::move(figures);
    capacity_ = capacity;
}

void Array::addFigure(std::unique_ptr<Figure> figure) {
    if (!figure) {
        return;
    }
    if (size_ >= capacity_) {
        resize(std::max<std::size_t>(1, capacity_ * 2));
    }
    figures_[size_++] = std::move(figure);
}

void Array::removeFigure(std::size_t index) {
    if (index >= size_) {
        return;
    }
    for (std::size_t i = index; i + 1 < size_; ++i) {
        figures_[i] = std::move(figures_[i + 1]);
    }
    figures_[--size_].reset();
}

Figure* Array::getFigure(std::size_t index) const {
    return index < size_ ? figures_[index].get() : nullptr;
}

Figure* Array::operator[](std::size_t index) const {
    return getFigure(index);
}

std::size_t Array::getSize() const {
    return size_;
}

std::size_t Array::getCapacity() const {
    return capacity_;
}

double Array::getAllArea() const {
    double sum = 0;
    for (std::size_t i = 0; i < size_; ++i) {
        sum += static_cast<double>(*figures_[i]);
    }
    return sum;
}

void Array::printFigures(std::ostream& os) const {
    for (std::size_t i = 0; i < size_; ++i) {
        os << "Figure " << i + 1 << ": " << *figures_[i] << " Center: " << figures_[i]->getCenter()
           << " Area: " << static_cast<double>(*figures_[i]) << '\n';
    }
}
