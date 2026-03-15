#pragma once

#include <memory_resource>
#include <string>

#include "vector_iterator.hpp"


template <typename T>
class Vector {
   private:
    std::pmr::polymorphic_allocator<T> alloc_;
    T* data_;
    size_t size_;
    size_t capacity_;

    void grow() {
        size_t capacity = (capacity_ == 0 ? 1 : capacity_ * 2);
        T* data = alloc_.allocate(capacity);

        for (size_t i = 0; i < size_; i++)
            new (data + i) T(std::move(data_[i]));

        for (size_t i = 0; i < size_; i++)
            data_[i].~T();

        if (data_)
            alloc_.deallocate(data_, capacity_);

        data_ = data;
        capacity_ = capacity;
    }

   public:
    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;

    Vector(std::pmr::memory_resource* mr = std::pmr::get_default_resource())
        : alloc_(mr), data_(nullptr), size_(0), capacity_(0) {
    }

    void push_back(const T& value) {
        if (size_ == capacity_)
            grow();
        new (data_ + size_) T(value);
        size_++;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    T& operator[](size_t i) {
        return data_[i];
    }

    const T& operator[](size_t i) const {
        return data_[i];
    }

    iterator begin() {
        return iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    const_iterator begin() const {
        return const_iterator(data_);
    }

    const_iterator end() const {
        return const_iterator(data_ + size_);
    }

    ~Vector() {
        for (size_t i = 0; i < size_; i++)
            data_[i].~T();
        if (data_)
            alloc_.deallocate(data_, capacity_);
    }
};
