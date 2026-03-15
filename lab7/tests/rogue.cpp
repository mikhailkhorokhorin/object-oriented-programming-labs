#include "rogue.hpp"

#include <gtest/gtest.h>

#include "bear.hpp"
#include "point.hpp"
#include "werewolf.hpp"

TEST(RogueTest, TypeAndPosition) {
    Rogue rogue("Rico", Point(15, 25));
    EXPECT_EQ(rogue.getName(), "Rico");
    EXPECT_EQ(rogue.getType(), "Rogue");
    EXPECT_EQ(rogue.getPosition().getX(), 15);
    EXPECT_EQ(rogue.getPosition().getY(), 25);
}

TEST(RogueTest, MoveAndKillDistance) {
    Rogue rogue("Rico", Point(0, 0));
    EXPECT_EQ(rogue.getMoveDistance(), 10);
    EXPECT_EQ(rogue.getKillDistance(), 10);
}

TEST(RogueTest, KillsLogic) {
    Rogue rogue("Rico", Point(0, 0));
    Bear bear("Ted", Point(0, 0));
    Werewolf wolf("Wolfy", Point(0, 0));

    EXPECT_TRUE(rogue.kills(bear));
    EXPECT_FALSE(rogue.kills(wolf));
}

TEST(RogueTest, AliveKill) {
    Rogue rogue("Rico", Point(0, 0));
    EXPECT_TRUE(rogue.isAlive());
    rogue.kill();
    EXPECT_FALSE(rogue.isAlive());
}

TEST(RogueTest, MoveWithinBounds) {
    Rogue rogue("Rico", Point(50, 50));
    rogue.move(20, 20, 100, 100);
    EXPECT_EQ(rogue.getPosition().getX(), 70);
    EXPECT_EQ(rogue.getPosition().getY(), 70);

    rogue.move(1000, 1000, 100, 100);
    EXPECT_EQ(rogue.getPosition().getX(), 100);
    EXPECT_EQ(rogue.getPosition().getY(), 100);

    rogue.move(-200, -200, 100, 100);
    EXPECT_EQ(rogue.getPosition().getX(), 0);
    EXPECT_EQ(rogue.getPosition().getY(), 0);
}
