#include "vector_iterator.hpp"

#include <gtest/gtest.h>

TEST(VectorIteratorTest, IterationOverIntArray) {
    int arr[] = {10, 20, 30};
    VectorIterator<int> it(arr);
    VectorIterator<int> end(arr + 3);

    int expected = 10;
    while (it != end) {
        EXPECT_EQ(*it, expected);
        ++it;
        expected += 10;
    }

    EXPECT_EQ(it, end);
}

TEST(VectorIteratorTest, PrefixAndPostfixIncrement) {
    int arr[] = {5, 15, 25};
    VectorIterator<int> it(arr);

    VectorIterator<int> it_post = it++;
    EXPECT_EQ(*it_post, 5);
    EXPECT_EQ(*it, 15);

    VectorIterator<int> it_pre = ++it;
    EXPECT_EQ(*it_pre, 25);
    EXPECT_EQ(*it, 25);
}

TEST(VectorIteratorTest, ArrowOperator) {
    struct Point {
        int x;
        int y;
    };
    
    Point points[] = {{1, 2}, {3, 4}};
    VectorIterator<Point> it(points);

    EXPECT_EQ(it->x, 1);
    EXPECT_EQ(it->y, 2);

    ++it;
    EXPECT_EQ(it->x, 3);
    EXPECT_EQ(it->y, 4);
}

TEST(VectorIteratorTest, ComparisonOperators) {
    int arr[] = {1, 2};
    VectorIterator<int> a(arr);
    VectorIterator<int> b(arr);
    VectorIterator<int> c(arr + 1);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);
}

TEST(VectorIteratorTest, EmptyArray) {
    int arr[0];
    VectorIterator<int> it(arr);
    VectorIterator<int> end(arr);

    EXPECT_EQ(it, end);
}

TEST(VectorIteratorTest, ConstArrayIteration) {
    const int arr[] = {100, 200, 300};
    VectorIterator<const int> it(arr);
    VectorIterator<const int> end(arr + 3);

    int expected = 100;
    for (; it != end; ++it) {
        EXPECT_EQ(*it, expected);
        expected += 100;
    }
}

TEST(VectorIteratorTest, MultipleIncrements) {
    int arr[] = {1, 2, 3, 4};
    VectorIterator<int> it(arr);

    ++it;
    it++;
    ++it;

    EXPECT_EQ(*it, 4);
}
