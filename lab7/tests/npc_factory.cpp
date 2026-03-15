#include "npc_factory.hpp"

#include <gtest/gtest.h>

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

TEST(NPCFactoryTest, CreateByType) {
    auto bear = NPCFactory::create("Bear", "Ted", 10, 20);
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "Ted");
    EXPECT_EQ(bear->getPosition().getX(), 10);
    EXPECT_EQ(bear->getPosition().getY(), 20);

    auto rogue = NPCFactory::create("Rogue", "Rico", 5, 15);
    ASSERT_NE(rogue, nullptr);
    EXPECT_EQ(rogue->getType(), "Rogue");

    auto wolf = NPCFactory::create("Werewolf", "Wolfy", 0, 0);
    ASSERT_NE(wolf, nullptr);
    EXPECT_EQ(wolf->getType(), "Werewolf");

    auto unknown = NPCFactory::create("Dragon", "Drago", 0, 0);
    EXPECT_EQ(unknown, nullptr);
}

TEST(NPCFactoryTest, FromString) {
    std::string line = "Bear Teddy 10 20";
    auto npc = NPCFactory::fromString(line);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Bear");
    EXPECT_EQ(npc->getName(), "Teddy");
    EXPECT_EQ(npc->getPosition().getX(), 10);
    EXPECT_EQ(npc->getPosition().getY(), 20);
}

TEST(NPCFactoryTest, CreateRandom) {
    const int WIDTH = 100;
    const int HEIGHT = 50;
    for (int i = 0; i < 100; ++i) {
        auto npc = NPCFactory::createRandom(WIDTH, HEIGHT);
        ASSERT_NE(npc, nullptr);
        EXPECT_GE(npc->getPosition().getX(), 0);
        EXPECT_LT(npc->getPosition().getX(), WIDTH);
        EXPECT_GE(npc->getPosition().getY(), 0);
        EXPECT_LT(npc->getPosition().getY(), HEIGHT);

        std::string type = npc->getType();
        EXPECT_TRUE(type == "Bear" || type == "Rogue" || type == "Werewolf");
    }
}
