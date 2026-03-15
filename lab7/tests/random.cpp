#include "random.hpp"

#include <gtest/gtest.h>

TEST(RandomTest, RollD6Range) {
    for (int i = 0; i < 1000; ++i) {
        int value = roll_d6();
        EXPECT_GE(value, 1);
        EXPECT_LE(value, 6);
    }
}

TEST(RandomTest, RollD6MultipleCalls) {
    int prev = roll_d6();
    bool differentObserved = false;
    for (int i = 0; i < 1000; ++i) {
        int current = roll_d6();
        if (current != prev) {
            differentObserved = true;
            break;
        }
    }
    EXPECT_TRUE(differentObserved);
}
