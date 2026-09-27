#include "vector.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <memory_resource>
#include <stdexcept>
#include <string>
#include <utility>

#include "memory_resource.hpp"

namespace {

struct Person {
    int id;
    std::string name;
};

Vector<std::string> makeWords(std::pmr::memory_resource* resource) {
    Vector<std::string> words(resource);
    words.pushBack("alpha");
    words.pushBack("beta");
    words.pushBack("gamma");
    return words;
}

}

TEST(VectorTest, StartsEmpty) {
    const Vector<int> vector;
    EXPECT_TRUE(vector.empty());
    EXPECT_EQ(vector.size(), 0U);
    EXPECT_EQ(vector.capacity(), 0U);
    EXPECT_EQ(vector.begin(), vector.end());
    EXPECT_EQ(vector.resource(), std::pmr::get_default_resource());
}

TEST(VectorTest, PushBackGrowsGeometrically) {
    Vector<int> vector;
    vector.pushBack(10);
    EXPECT_EQ(vector.capacity(), 1U);
    vector.pushBack(20);
    vector.pushBack(30);
    EXPECT_EQ(vector.size(), 3U);
    EXPECT_EQ(vector.capacity(), 4U);
    EXPECT_EQ(vector[0], 10);
    EXPECT_EQ(vector[2], 30);
    vector[1] = 100;
    EXPECT_EQ(vector.at(1), 100);
}

TEST(VectorTest, AtChecksBounds) {
    Vector<int> vector;
    vector.pushBack(1);
    const Vector<int>& constVector = vector;
    EXPECT_EQ(constVector.at(0), 1);
    EXPECT_THROW(vector.at(1), std::out_of_range);
    EXPECT_THROW(constVector.at(5), std::out_of_range);
}

TEST(VectorTest, PopBackAndClear) {
    Vector<std::string> vector = makeWords(std::pmr::get_default_resource());
    vector.popBack();
    EXPECT_EQ(vector.size(), 2U);
    EXPECT_EQ(vector[1], "beta");
    vector.clear();
    EXPECT_TRUE(vector.empty());
    EXPECT_THROW(vector.popBack(), std::out_of_range);
}

TEST(VectorTest, ReserveKeepsElements) {
    Vector<std::string> vector = makeWords(std::pmr::get_default_resource());
    vector.reserve(16);
    EXPECT_EQ(vector.capacity(), 16U);
    vector.reserve(2);
    EXPECT_EQ(vector.capacity(), 16U);
    EXPECT_EQ(vector[2], "gamma");
}

TEST(VectorTest, EmplaceBackStoresStructs) {
    Vector<Person> people;
    people.pushBack({1, "Alice"});
    Person& bob = people.emplaceBack(Person{2, "Bob"});
    EXPECT_EQ(bob.name, "Bob");
    EXPECT_EQ(people[0].id, 1);
    EXPECT_EQ(people.size(), 2U);
}

TEST(VectorTest, IteratesWithStandardAlgorithms) {
    Vector<int> vector;
    for (int value : {3, 1, 2}) {
        vector.pushBack(value);
    }
    std::sort(vector.begin().get(), vector.end().get());
    const Vector<int>& constVector = vector;
    int expected = 1;
    for (const int value : constVector) {
        EXPECT_EQ(value, expected++);
    }
    EXPECT_NE(std::find(constVector.begin(), constVector.end(), 2), constVector.end());
}

TEST(VectorTest, CopyIsIndependent) {
    const Vector<std::string> original = makeWords(std::pmr::get_default_resource());
    Vector<std::string> copy(original);
    copy[0] = "changed";
    copy.pushBack("delta");
    EXPECT_EQ(original[0], "alpha");
    EXPECT_EQ(original.size(), 3U);
    EXPECT_EQ(copy.size(), 4U);

    Vector<std::string> assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), 3U);
    EXPECT_EQ(assigned[2], "gamma");
    const Vector<std::string>& alias = assigned;
    assigned = alias;
    EXPECT_EQ(assigned.size(), 3U);
}

TEST(VectorTest, MoveTransfersStorage) {
    Vector<std::string> source = makeWords(std::pmr::get_default_resource());
    const std::string* data = &source[0];
    Vector<std::string> moved(std::move(source));
    EXPECT_EQ(&moved[0], data);
    EXPECT_EQ(moved.size(), 3U);

    Vector<std::string> assigned;
    assigned.pushBack("old");
    assigned = std::move(moved);
    EXPECT_EQ(assigned.size(), 3U);
    EXPECT_EQ(&assigned[0], data);
}

TEST(VectorTest, AllocatesThroughMemoryResource) {
    MemoryResource resource;
    {
        Vector<int> vector(&resource);
        EXPECT_EQ(vector.resource(), &resource);
        for (int i = 0; i < 5; ++i) {
            vector.pushBack(i);
        }
        EXPECT_EQ(resource.usedBlockCount(), 1U);
        EXPECT_EQ(resource.freeBlockCount(), 3U);

        const Vector<int> copy(vector);
        EXPECT_EQ(copy.resource(), &resource);
        EXPECT_EQ(resource.usedBlockCount(), 2U);
    }
    EXPECT_EQ(resource.usedBlockCount(), 0U);
    EXPECT_EQ(resource.freeBlockCount(), 5U);
}

TEST(VectorTest, WorksWithMonotonicResource) {
    std::pmr::monotonic_buffer_resource resource(1024);
    Vector<std::string> words = makeWords(&resource);
    EXPECT_EQ(words[1], "beta");
}
