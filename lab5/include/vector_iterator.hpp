#pragma once

#include <iterator>

template <typename T>
class VectorIterator {
   private:
    T* ptr_;

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VectorIterator(T* p = nullptr) : ptr_(p) {
    }

    reference operator*() const {
        return *ptr_;
    }

    pointer operator->() const {
        return ptr_;
    }

    VectorIterator& operator++() {
        ++ptr_;
        return *this;
    }

    VectorIterator operator++(int) {
        VectorIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const VectorIterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const VectorIterator& other) const {
        return ptr_ != other.ptr_;
    }
};
