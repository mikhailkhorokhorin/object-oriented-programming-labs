#include "npc_factory.hpp"

#include <gtest/gtest.h>

#include <random>
#include <set>
#include <stdexcept>
#include <string>

TEST(NPCFactoryTest, CreatesEveryType) {
    for (const std::string type : {"Bear", "Rogue", "Werewolf"}) {
        const auto npc = NPCFactory::create(type, "Name", 10, 20);
        ASSERT_NE(npc, nullptr) << type;
        EXPECT_EQ(npc->getType(), type);
        EXPECT_EQ(npc->getPosition(), Point(10, 20));
    }
    EXPECT_EQ(NPCFactory::create("Dragon", "Drako", 0, 0), nullptr);
}

TEST(NPCFactoryTest, ParsesLine) {
    const auto npc = NPCFactory::fromString("Rogue Robin 3 4");
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Robin");
    EXPECT_EQ(npc->getPosition(), Point(3, 4));
    EXPECT_EQ(NPCFactory::fromString("Rogue Robin"), nullptr);
}

TEST(NPCFactoryTest, RandomNPCsAreInsideMap) {
    std::mt19937 engine(7);
    std::set<std::string> types;
    for (int id = 1; id <= 200; ++id) {
        const auto npc = NPCFactory::createRandom(id, 10, 5, engine);
        ASSERT_NE(npc, nullptr);
        EXPECT_EQ(npc->getName(), npc->getType() + "_" + std::to_string(id));
        const Point position = npc->getPosition();
        EXPECT_GE(position.getX(), 0);
        EXPECT_LT(position.getX(), 10);
        EXPECT_GE(position.getY(), 0);
        EXPECT_LT(position.getY(), 5);
        types.insert(npc->getType());
    }
    EXPECT_EQ(types.size(), 3U);
}

TEST(NPCFactoryTest, RandomRejectsEmptyMap) {
    std::mt19937 engine(7);
    EXPECT_THROW(NPCFactory::createRandom(1, 0, 10, engine), std::invalid_argument);
}
