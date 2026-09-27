#include "npc_factory.hpp"

#include <gtest/gtest.h>

TEST(NPCFactoryTest, CreatesEveryType) {
    for (const std::string type : {"Bear", "Rogue", "Werewolf"}) {
        const auto npc = NPCFactory::create(type, "Name", 10, 20);
        ASSERT_NE(npc, nullptr) << type;
        EXPECT_EQ(npc->getType(), type);
        EXPECT_EQ(npc->getName(), "Name");
        EXPECT_EQ(npc->getPosition(), Point(10, 20));
    }
}

TEST(NPCFactoryTest, UnknownTypeGivesNull) {
    EXPECT_EQ(NPCFactory::create("Dragon", "Drako", 0, 0), nullptr);
}

TEST(NPCFactoryTest, ParsesLine) {
    const auto npc = NPCFactory::fromString("Werewolf Lupin 7 14");
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Werewolf");
    EXPECT_EQ(npc->getName(), "Lupin");
    EXPECT_EQ(npc->getPosition(), Point(7, 14));
}

TEST(NPCFactoryTest, RejectsMalformedLine) {
    EXPECT_EQ(NPCFactory::fromString(""), nullptr);
    EXPECT_EQ(NPCFactory::fromString("Bear Baloo"), nullptr);
    EXPECT_EQ(NPCFactory::fromString("Bear Baloo x 1"), nullptr);
    EXPECT_EQ(NPCFactory::fromString("Dragon Drako 1 1"), nullptr);
}
