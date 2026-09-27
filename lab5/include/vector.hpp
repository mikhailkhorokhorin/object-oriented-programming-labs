#pragma once

#include <cstddef>
#include <memory>
#include <memory_resource>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "vector_iterator.hpp"

template <typename T>
class Vector {
public:
    using value_type = T;
    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;

    Vector() : Vector(std::pmr::get_default_resource()) {}

    explicit Vector(std::pmr::memory_resource* resource) : resource_(resource) {}

    Vector(const Vector& other) : resource_(other.resource_) {
        reserve(other.size_);
        for (const T& value : other) {
            pushBack(value);
        }
    }

    Vector(Vector&& other) noexcept
        : resource_(other.resource_),
          data_(std::exchange(other.data_, nullptr)),
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)) {}

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector copy(other);
            swap(copy);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            Vector moved(std::move(other));
            swap(moved);
        }
        return *this;
    }

    ~Vector() {
        clear();
        release();
    }

    void pushBack(const T& value) { emplaceBack(value); }

    void pushBack(T&& value) { emplaceBack(std::move(value)); }

    template <typename... Args>
    T& emplaceBack(Args&&... args) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        T* slot = std::construct_at(data_ + size_, std::forward<Args>(args)...);
        ++size_;
        return *slot;
    }

    void popBack() {
        if (size_ == 0) {
            throw std::out_of_range("popBack on empty Vector");
        }
        --size_;
        std::destroy_at(data_ + size_);
    }

    void clear() noexcept {
        std::destroy(data_, data_ + size_);
        size_ = 0;
    }

    void reserve(std::size_t capacity) {
        if (capacity <= capacity_) {
            return;
        }
        T* data = allocator().allocate(capacity);
        for (std::size_t i = 0; i < size_; ++i) {
            std::construct_at(data + i, std::move_if_noexcept(data_[i]));
        }
        std::destroy(data_, data_ + size_);
        release();
        data_ = data;
        capacity_ = capacity;
    }

    std::size_t size() const { return size_; }

    std::size_t capacity() const { return capacity_; }

    bool empty() const { return size_ == 0; }

    std::pmr::memory_resource* resource() const { return resource_; }

    T& operator[](std::size_t index) { return data_[index]; }

    const T& operator[](std::size_t index) const { return data_[index]; }

    T& at(std::size_t index) {
        checkIndex(index);
        return data_[index];
    }

    const T& at(std::size_t index) const {
        checkIndex(index);
        return data_[index];
    }

    iterator begin() { return iterator(data_); }

    iterator end() { return iterator(data_ + size_); }

    const_iterator begin() const { return const_iterator(data_); }

    const_iterator end() const { return const_iterator(data_ + size_); }

private:
    std::pmr::memory_resource* resource_;
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void release() noexcept {
        if (data_ != nullptr) {
            allocator().deallocate(data_, capacity_);
            data_ = nullptr;
            capacity_ = 0;
        }
    }

    void checkIndex(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
    }

    std::pmr::polymorphic_allocator<T> allocator() const {
        return std::pmr::polymorphic_allocator<T>(resource_);
    }

    void swap(Vector& other) noexcept {
        std::swap(resource_, other.resource_);
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};
