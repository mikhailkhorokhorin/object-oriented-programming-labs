#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>

template <typename T>
class VectorIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::remove_cv_t<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VectorIterator() = default;

    explicit VectorIterator(T* ptr) : ptr_(ptr) {}

    template <typename U>
        requires std::is_convertible_v<U*, T*>
    VectorIterator(const VectorIterator<U>& other) : ptr_(other.get()) {}

    reference operator*() const { return *ptr_; }

    pointer operator->() const { return ptr_; }

    VectorIterator& operator++() {
        ++ptr_;
        return *this;
    }

    VectorIterator operator++(int) {
        VectorIterator previous = *this;
        ++ptr_;
        return previous;
    }

    pointer get() const { return ptr_; }

    bool operator==(const VectorIterator& other) const = default;

private:
    T* ptr_ = nullptr;
};
