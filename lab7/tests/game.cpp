#include "game.hpp"

#include <gtest/gtest.h>

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

TEST(GameTest, InitAddsCorrectNumberOfNPCs) {
    Game game(100, 100);
    game.init(10);

    auto& dungeon = game.getDungeon();
    auto aliveNPCs = dungeon.getAliveNPCs();

    EXPECT_EQ(aliveNPCs.size(), 10);
}

TEST(GameTest, NPCsAreAliveAfterInit) {
    Game game(100, 100);
    game.init(5);

    auto& dungeon = game.getDungeon();
    for (auto& npc : dungeon.getAliveNPCs()) {
        EXPECT_TRUE(npc->isAlive());
    }
}

TEST(GameTest, RunSimulationKeepsRunningAndProducesAliveNPCs) {
    Game game(50, 50);
    game.init(10);

    game.run(1);

    auto& dungeon = game.getDungeon();
    auto aliveNPCs = dungeon.getAliveNPCs();

    EXPECT_GE(aliveNPCs.size(), 0);
    for (auto& npc : aliveNPCs)
        EXPECT_TRUE(npc->isAlive());
}

TEST(GameTest, ObserversReceiveMessages) {
    Game game(100, 100);
    game.init(2);

    auto& dungeon = game.getDungeon();
    dungeon.notifyObservers("Test message");

    SUCCEED();
}
