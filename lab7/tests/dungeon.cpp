#include "dungeon.hpp"

#include <gtest/gtest.h>

#include "bear.hpp"
#include "npc_factory.hpp"
#include "observer_console.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

class MockObserver : public IObserver {
   public:
    std::vector<std::string> events;
    void onEvent(const std::string& msg) override {
        events.push_back(msg);
    }
};

TEST(DungeonTest, SpawnRandomNPCsCreatesCorrectCount) {
    Dungeon dungeon(100, 100);
    dungeon.spawnRandomNPCs(10);

    auto alive = dungeon.getAliveNPCs();
    EXPECT_EQ(alive.size(), 10);
}

TEST(DungeonTest, AddObserverAndNotify) {
    Dungeon dungeon(100, 100);
    MockObserver observer;
    dungeon.addObserver(&observer);

    dungeon.notifyObservers("TestEvent");
    ASSERT_EQ(observer.events.size(), 1);
    EXPECT_EQ(observer.events[0], "TestEvent");
}

TEST(DungeonTest, GetAliveNPCsFiltersDeadNPCs) {
    Dungeon dungeon(100, 100);
    auto npc1 = NPCFactory::create("Bear", "B1", 0, 0);
    auto npc2 = NPCFactory::create("Rogue", "R1", 1, 1);
    npc2->kill();

    dungeon.addNPCInstance(npc1);
    dungeon.addNPCInstance(npc2);

    auto alive = dungeon.getAliveNPCs();
    ASSERT_EQ(alive.size(), 1);
    EXPECT_EQ(alive[0]->getName(), "B1");
}

TEST(DungeonTest, PrintMapDoesNotCrash) {
    Dungeon dungeon(100, 100);
    dungeon.spawnRandomNPCs(5);
    EXPECT_NO_THROW(dungeon.printMap());
}

TEST(DungeonTest, AddNPCInstanceStoresCorrectTypes) {
    Dungeon dungeon(100, 100);
    auto bear = std::make_shared<Bear>("Bear1", Point(10, 20));
    auto rogue = std::make_shared<Rogue>("Rogue1", Point(5, 5));
    auto werewolf = std::make_shared<Werewolf>("Wolf1", Point(7, 7));

    dungeon.addNPCInstance(bear);
    dungeon.addNPCInstance(rogue);
    dungeon.addNPCInstance(werewolf);

    auto alive = dungeon.getAliveNPCs();
    ASSERT_EQ(alive.size(), 3);
    EXPECT_EQ(alive[0]->getType(), "Bear");
    EXPECT_EQ(alive[1]->getType(), "Rogue");
    EXPECT_EQ(alive[2]->getType(), "Werewolf");
}

TEST(DungeonTest, ManualKillNotifiesObservers) {
    Dungeon dungeon(100, 100);
    MockObserver observer;
    dungeon.addObserver(&observer);

    auto npc1 = NPCFactory::create("Bear", "Bear1", 0, 0);
    auto npc2 = NPCFactory::create("Werewolf", "Wolf1", 0, 0);

    dungeon.addNPCInstance(npc1);
    dungeon.addNPCInstance(npc2);

    npc2->kill();
    dungeon.notifyObservers(npc1->getName() + " killed " + npc2->getName());

    ASSERT_EQ(observer.events.size(), 1);
    EXPECT_EQ(observer.events[0], "Bear1 killed Wolf1");
}

TEST(DungeonTest, NPCKillChangesAliveStatus) {
    auto npc = NPCFactory::create("Bear", "Bear1", 0, 0);
    EXPECT_TRUE(npc->isAlive());
    npc->kill();
    EXPECT_FALSE(npc->isAlive());
}

TEST(DungeonTest, NPCMoveWithinBounds) {
    auto npc = NPCFactory::create("Bear", "Bear1", 50, 50);
    npc->move(60, 60, 100, 100);
    auto pos = npc->getPosition();
    EXPECT_LE(pos.getX(), 100);
    EXPECT_LE(pos.getY(), 100);

    npc->move(-200, -200, 100, 100);
    pos = npc->getPosition();
    EXPECT_GE(pos.getX(), 0);
    EXPECT_GE(pos.getY(), 0);
}
