#include "vector.hpp"

#include <gtest/gtest.h>

#include "vector_iterator.hpp"

TEST(VectorTest, PushBackAndSize) {
    std::pmr::monotonic_buffer_resource mr(1024);
    Vector<int> vec(&mr);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);

    vec.push_back(10);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GE(vec.capacity(), 1);

    vec.push_back(20);
    vec.push_back(30);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_GE(vec.capacity(), 3);
}

TEST(VectorTest, IndexOperator) {
    std::pmr::monotonic_buffer_resource mr(1024);
    Vector<int> vec(&mr);

    vec.push_back(5);
    vec.push_back(15);
    vec.push_back(25);

    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 15);
    EXPECT_EQ(vec[2], 25);

    vec[1] = 100;
    EXPECT_EQ(vec[1], 100);
}

TEST(VectorTest, Iteration) {
    std::pmr::monotonic_buffer_resource mr(1024);
    Vector<int> vec(&mr);

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    int expected = 1;
    for (auto it = vec.begin(); it != vec.end(); ++it)
        EXPECT_EQ(*it, expected++);
}

TEST(VectorTest, ConstVectorIteration) {
    std::pmr::monotonic_buffer_resource mr(1024);
    Vector<int> vec(&mr);

    vec.push_back(10);
    vec.push_back(20);

    const Vector<int>& cvec = vec;
    int expected = 10;
    for (auto it = cvec.begin(); it != cvec.end(); ++it) {
        EXPECT_EQ(*it, expected);
        expected += 10;
    }
}

TEST(VectorTest, IteratorTraits) {
    using Iter = Vector<int>::iterator;
    EXPECT_TRUE((std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                              std::forward_iterator_tag>::value));
}

struct Struct {
    int x;
    double y;
    std::string name;

    bool operator==(const Struct& other) const {
        return x == other.x && y == other.y && name == other.name;
    }
};

TEST(VectorTest, CustomType) {
    std::pmr::monotonic_buffer_resource mr(1024);
    Vector<Struct> vec(&mr);

    vec.push_back({1, 2.5, "Alice"});
    vec.push_back({3, 4.7, "Bob"});

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], (Struct{1, 2.5, "Alice"}));
    EXPECT_EQ(vec[1], (Struct{3, 4.7, "Bob"}));

    int count = 0;
    for (auto& item : vec) {
        if (count == 0)
            EXPECT_EQ(item.name, "Alice");
        if (count == 1)
            EXPECT_EQ(item.name, "Bob");
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST(VectorTest, CapacityGrowth) {
    std::pmr::monotonic_buffer_resource mr(1024);
    Vector<int> vec(&mr);

    size_t prevCapacity = vec.capacity();
    for (int i = 0; i < 100; i++) {
        vec.push_back(i);
        EXPECT_GE(vec.capacity(), vec.size());
        EXPECT_GE(vec.capacity(), prevCapacity);
        prevCapacity = vec.capacity();
    }
}
