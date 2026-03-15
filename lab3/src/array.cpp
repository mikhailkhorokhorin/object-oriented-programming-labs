#include "array.hpp"

void Array::resize(size_t capacity) {
    Figure** figures = new Figure*[capacity];
    for (size_t i = 0; i < size_; ++i)
        figures[i] = figures_[i];

    for (size_t i = size_; i < capacity; ++i)
        figures[i] = nullptr;

    delete[] figures_;

    figures_ = figures;
    capacity_ = capacity;
}

Array::Array(size_t capacity) : size_(0), capacity_(capacity) {
    figures_ = new Figure*[capacity_];

    for (size_t i = 0; i < capacity_; ++i)
        figures_[i] = nullptr;
}

Array::Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
    figures_ = new Figure*[capacity_];

    for (size_t i = 0; i < size_; ++i)
        figures_[i] = other.figures_[i]->clone().release();
}

Array::Array(Array&& other) noexcept
    : figures_(other.figures_), size_(other.size_), capacity_(other.capacity_) {
    other.figures_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Array& Array::operator=(Array&& other) noexcept {
    std::swap(figures_, other.figures_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    return *this;
}

Array& Array::operator=(const Array& other) {
    if (this == &other)
        return *this;

    Figure** figures = new Figure*[other.capacity_];
    for (size_t i = 0; i < other.size_; ++i)
        figures[i] = other.figures_[i]->clone().release();
    for (size_t i = other.size_; i < other.capacity_; ++i)
        figures[i] = nullptr;

    for (size_t i = 0; i < size_; ++i)
        delete figures_[i];
    delete[] figures_;

    figures_ = figures;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}

Array::~Array() {
    for (size_t i = 0; i < size_; ++i)
        delete figures_[i];

    delete[] figures_;
}

void Array::addFigure(Figure* figure) {
    if (size_ >= capacity_)
        resize(capacity_ * 2);

    figures_[size_++] = figure;
}

void Array::removeFigure(size_t index) {
    if (index >= size_)
        return;

    delete figures_[index];
    for (size_t i = index; i < size_ - 1; ++i)
        figures_[i] = figures_[i + 1];

    --size_;
}

Figure* Array::getFigure(size_t index) const {
    if (index >= size_)
        return nullptr;

    return figures_[index];
}

size_t Array::getSize() const {
    return size_;
}
size_t Array::getCapacity() const {
    return capacity_;
}

double Array::getAllArea() const {
    double sum = 0;

    for (size_t i = 0; i < size_; ++i)
        sum += static_cast<double>(*figures_[i]);

    return sum;
}

void Array::printFigures() const {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Figure " << i + 1 << ": ";
        figures_[i]->print(std::cout);

        Point center = figures_[i]->getCenter();
        std::cout << "Center: (" << center.x << ", " << center.y << ") ";
        std::cout << "Area: " << static_cast<double>(*figures_[i]) << std::endl;
    }
}

Figure* Array::operator[](size_t index) const {
    if (index >= size_)
        return nullptr;
    return figures_[index];
}