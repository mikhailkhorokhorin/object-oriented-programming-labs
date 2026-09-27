#include "vector_iterator.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <iterator>
#include <type_traits>

static_assert(std::forward_iterator<VectorIterator<int>>);
static_assert(std::forward_iterator<VectorIterator<const int>>);
static_assert(std::is_same_v<std::iterator_traits<VectorIterator<const int>>::value_type, int>);

TEST(VectorIteratorTest, WalksArray) {
    std::array<int, 3> values{10, 20, 30};
    VectorIterator<int> it(values.data());
    const VectorIterator<int> end(values.data() + values.size());
    int expected = 10;
    for (; it != end; ++it) {
        EXPECT_EQ(*it, expected);
        expected += 10;
    }
    EXPECT_EQ(it, end);
}

TEST(VectorIteratorTest, PrefixAndPostfixIncrement) {
    std::array<int, 3> values{5, 15, 25};
    VectorIterator<int> it(values.data());
    const VectorIterator<int> previous = it++;
    EXPECT_EQ(*previous, 5);
    EXPECT_EQ(*it, 15);
    const VectorIterator<int> next = ++it;
    EXPECT_EQ(*next, 25);
    EXPECT_EQ(next, it);
}

TEST(VectorIteratorTest, ArrowAndWriteThrough) {
    struct Pair {
        int first;
        int second;
    };
    std::array<Pair, 2> pairs{{{1, 2}, {3, 4}}};
    VectorIterator<Pair> it(pairs.data());
    EXPECT_EQ(it->second, 2);
    it->first = 7;
    EXPECT_EQ(pairs[0].first, 7);
    EXPECT_EQ(it.get(), pairs.data());
}

TEST(VectorIteratorTest, DefaultAndConstConversion) {
    const VectorIterator<int> empty;
    EXPECT_EQ(empty.get(), nullptr);
    std::array<int, 2> values{1, 2};
    const VectorIterator<int> mutableIt(values.data());
    const VectorIterator<const int> constIt = mutableIt;
    EXPECT_EQ(*constIt, 1);
}

TEST(VectorIteratorTest, WorksWithStandardAlgorithms) {
    std::array<int, 4> values{4, 8, 15, 16};
    const VectorIterator<int> begin(values.data());
    const VectorIterator<int> end(values.data() + values.size());
    EXPECT_EQ(std::distance(begin, end), 4);
    EXPECT_EQ(*std::find(begin, end, 15), 15);
}
