#include "random.hpp"

#include <gtest/gtest.h>

#include <array>
#include <thread>
#include <vector>

TEST(RandomTest, RollsEveryFaceWithinRange) {
    std::array<int, 7> counts{};
    for (int i = 0; i < 6000; ++i) {
        const int roll = rollD6();
        ASSERT_GE(roll, 1);
        ASSERT_LE(roll, 6);
        ++counts.at(static_cast<std::size_t>(roll));
    }
    for (int face = 1; face <= 6; ++face) {
        EXPECT_GT(counts.at(static_cast<std::size_t>(face)), 500) << face;
    }
}

TEST(RandomTest, SafeToCallFromManyThreads) {
    std::vector<std::jthread> threads;
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([] {
            for (int i = 0; i < 1000; ++i) {
                const int roll = rollD6();
                EXPECT_TRUE(roll >= 1 && roll <= 6);
            }
        });
    }
}
