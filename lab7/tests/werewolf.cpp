#include "werewolf.hpp"

#include <gtest/gtest.h>

#include "bear.hpp"
#include "point.hpp"
#include "rogue.hpp"

TEST(WerewolfTest, TypeAndPosition) {
    Werewolf wolf("Wolfy", Point(30, 40));
    EXPECT_EQ(wolf.getName(), "Wolfy");
    EXPECT_EQ(wolf.getType(), "Werewolf");
    EXPECT_EQ(wolf.getPosition().getX(), 30);
    EXPECT_EQ(wolf.getPosition().getY(), 40);
}

TEST(WerewolfTest, MoveAndKillDistance) {
    Werewolf wolf("Wolfy", Point(0, 0));
    EXPECT_EQ(wolf.getMoveDistance(), 40);
    EXPECT_EQ(wolf.getKillDistance(), 5);
}

TEST(WerewolfTest, KillsLogic) {
    Werewolf wolf("Wolfy", Point(0, 0));
    Rogue rogue("Rico", Point(0, 0));
    Bear bear("Ted", Point(0, 0));

    EXPECT_TRUE(wolf.kills(rogue));
    EXPECT_FALSE(wolf.kills(bear));
}

TEST(WerewolfTest, AliveKill) {
    Werewolf wolf("Wolfy", Point(0, 0));
    EXPECT_TRUE(wolf.isAlive());
    wolf.kill();
    EXPECT_FALSE(wolf.isAlive());
}

TEST(WerewolfTest, MoveWithinBounds) {
    Werewolf wolf("Wolfy", Point(50, 50));
    wolf.move(40, 40, 100, 100);
    EXPECT_EQ(wolf.getPosition().getX(), 90);
    EXPECT_EQ(wolf.getPosition().getY(), 90);

    wolf.move(1000, 1000, 100, 100);
    EXPECT_EQ(wolf.getPosition().getX(), 100);
    EXPECT_EQ(wolf.getPosition().getY(), 100);

    wolf.move(-200, -200, 100, 100);
    EXPECT_EQ(wolf.getPosition().getX(), 0);
    EXPECT_EQ(wolf.getPosition().getY(), 0);
}
