#include "bear.hpp"

#include <gtest/gtest.h>

#include "point.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

TEST(BearTest, TypeAndPosition) {
    Bear bear("Ted", Point(10, 20));
    EXPECT_EQ(bear.getName(), "Ted");
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bear.getPosition().getX(), 10);
    EXPECT_EQ(bear.getPosition().getY(), 20);
}

TEST(BearTest, MoveAndKillDistance) {
    Bear bear("Ted", Point(0, 0));
    EXPECT_EQ(bear.getMoveDistance(), 5);
    EXPECT_EQ(bear.getKillDistance(), 10);
}

TEST(BearTest, KillsLogic) {
    Bear bear("Ted", Point(0, 0));
    Rogue rogue("Rico", Point(0, 0));
    Werewolf wolf("Wolfy", Point(0, 0));

    EXPECT_FALSE(bear.kills(rogue));
    EXPECT_TRUE(bear.kills(wolf));
}

TEST(BearTest, AliveKill) {
    Bear bear("Ted", Point(0, 0));
    EXPECT_TRUE(bear.isAlive());
    bear.kill();
    EXPECT_FALSE(bear.isAlive());
}

TEST(BearTest, MoveWithinBounds) {
    Bear bear("Ted", Point(50, 50));
    bear.move(10, 10, 100, 100);
    EXPECT_EQ(bear.getPosition().getX(), 60);
    EXPECT_EQ(bear.getPosition().getY(), 60);

    bear.move(1000, 1000, 100, 100);
    EXPECT_EQ(bear.getPosition().getX(), 100);
    EXPECT_EQ(bear.getPosition().getY(), 100);

    bear.move(-200, -200, 100, 100);
    EXPECT_EQ(bear.getPosition().getX(), 0);
    EXPECT_EQ(bear.getPosition().getY(), 0);
}
