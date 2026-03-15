#include "npc_factory.hpp"

#include "bear.hpp"
#include "gtest/gtest.h"
#include "rogue.hpp"
#include "werewolf.hpp"

TEST(NPCFactoryTest, CreateBear) {
    std::shared_ptr<NPC> bear = NPCFactory::create("Bear", "Baloo", 10, 20);
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "Baloo");
    EXPECT_EQ(bear->getPosition().getX(), 10);
    EXPECT_EQ(bear->getPosition().getY(), 20);
}

TEST(NPCFactoryTest, CreateRogue) {
    std::shared_ptr<NPC> rogue = NPCFactory::create("Rogue", "Robin", 5, 15);
    ASSERT_NE(rogue, nullptr);
    EXPECT_EQ(rogue->getType(), "Rogue");
    EXPECT_EQ(rogue->getName(), "Robin");
    EXPECT_EQ(rogue->getPosition().getX(), 5);
    EXPECT_EQ(rogue->getPosition().getY(), 15);
}

TEST(NPCFactoryTest, CreateWerewolf) {
    std::shared_ptr<NPC> werewolf = NPCFactory::create("Werewolf", "Lupin", 7, 14);
    ASSERT_NE(werewolf, nullptr);
    EXPECT_EQ(werewolf->getType(), "Werewolf");
    EXPECT_EQ(werewolf->getName(), "Lupin");
    EXPECT_EQ(werewolf->getPosition().getX(), 7);
    EXPECT_EQ(werewolf->getPosition().getY(), 14);
}

TEST(NPCFactoryTest, CreateUnknownType) {
    std::shared_ptr<NPC> unknown1 = NPCFactory::create("Dragon", "Drako", 0, 0);
    EXPECT_EQ(unknown1, nullptr);
}

TEST(NPCFactoryTest, FromStringCreatesBear) {
    std::shared_ptr<NPC> bearFromString = NPCFactory::fromString("Bear Baloo 10 20");
    ASSERT_NE(bearFromString, nullptr);
    EXPECT_EQ(bearFromString->getType(), "Bear");
    EXPECT_EQ(bearFromString->getName(), "Baloo");
    EXPECT_EQ(bearFromString->getPosition().getX(), 10);
    EXPECT_EQ(bearFromString->getPosition().getY(), 20);
}

TEST(NPCFactoryTest, FromStringCreatesRogue) {
    std::shared_ptr<NPC> rogueFromString = NPCFactory::fromString("Rogue Robin 5 15");
    ASSERT_NE(rogueFromString, nullptr);
    EXPECT_EQ(rogueFromString->getType(), "Rogue");
    EXPECT_EQ(rogueFromString->getName(), "Robin");
    EXPECT_EQ(rogueFromString->getPosition().getX(), 5);
    EXPECT_EQ(rogueFromString->getPosition().getY(), 15);
}

TEST(NPCFactoryTest, FromStringCreatesWerewolf) {
    std::shared_ptr<NPC> werewolfFromString = NPCFactory::fromString("Werewolf Lupin 7 14");
    ASSERT_NE(werewolfFromString, nullptr);
    EXPECT_EQ(werewolfFromString->getType(), "Werewolf");
    EXPECT_EQ(werewolfFromString->getName(), "Lupin");
    EXPECT_EQ(werewolfFromString->getPosition().getX(), 7);
    EXPECT_EQ(werewolfFromString->getPosition().getY(), 14);
}

TEST(NPCFactoryTest, FromStringUnknownType) {
    std::shared_ptr<NPC> unknownFromString = NPCFactory::fromString("Dragon Drako 0 0");
    EXPECT_EQ(unknownFromString, nullptr);
}
