#include "npc.hpp"

#include <gtest/gtest.h>

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

TEST(NPCTest, TypesAndDistances) {
    const Bear bear("Baloo", Point(1, 2));
    const Rogue rogue("Robin", Point(4, 6));
    const Werewolf werewolf("Lupin", Point());
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(rogue.getType(), "Rogue");
    EXPECT_EQ(werewolf.getType(), "Werewolf");
    EXPECT_EQ(bear.getName(), "Baloo");
    EXPECT_EQ(bear.getPosition(), Point(1, 2));
    EXPECT_EQ(bear.getMoveDistance(), 5);
    EXPECT_EQ(bear.getKillDistance(), 10);
    EXPECT_EQ(rogue.getMoveDistance(), 10);
    EXPECT_EQ(rogue.getKillDistance(), 10);
    EXPECT_EQ(werewolf.getMoveDistance(), 40);
    EXPECT_EQ(werewolf.getKillDistance(), 5);
    EXPECT_DOUBLE_EQ(bear.distanceTo(rogue), 5.0);
}

TEST(NPCTest, KillRules) {
    const Bear bear("B", Point());
    const Rogue rogue("R", Point());
    const Werewolf werewolf("W", Point());
    EXPECT_TRUE(bear.kills(werewolf));
    EXPECT_TRUE(werewolf.kills(rogue));
    EXPECT_TRUE(rogue.kills(bear));
    EXPECT_FALSE(bear.kills(rogue));
    EXPECT_FALSE(werewolf.kills(bear));
    EXPECT_FALSE(rogue.kills(werewolf));
    EXPECT_FALSE(bear.kills(bear));
}

TEST(NPCTest, TryKillSucceedsOnce) {
    Bear bear("Baloo", Point());
    EXPECT_TRUE(bear.isAlive());
    EXPECT_TRUE(bear.tryKill());
    EXPECT_FALSE(bear.isAlive());
    EXPECT_FALSE(bear.tryKill());
}

TEST(NPCTest, ConcurrentTryKillHasSingleWinner) {
    Rogue rogue("Robin", Point());
    std::atomic<int> winners = 0;
    {
        std::vector<std::jthread> threads;
        for (int i = 0; i < 8; ++i) {
            threads.emplace_back([&rogue, &winners] {
                if (rogue.tryKill()) {
                    ++winners;
                }
            });
        }
    }
    EXPECT_EQ(winners.load(), 1);
}

TEST(NPCTest, MoveStaysInsideMap) {
    Werewolf werewolf("Lupin", Point(5, 5));
    werewolf.move(-40, -40, 10, 10);
    EXPECT_EQ(werewolf.getPosition(), Point(0, 0));
    werewolf.move(40, 40, 10, 10);
    EXPECT_EQ(werewolf.getPosition(), Point(9, 9));
    werewolf.move(-3, 0, 10, 10);
    EXPECT_EQ(werewolf.getPosition(), Point(6, 9));
}

TEST(NPCTest, DeadNPCDoesNotMove) {
    Bear bear("Baloo", Point(5, 5));
    bear.tryKill();
    bear.move(1, 1, 10, 10);
    EXPECT_EQ(bear.getPosition(), Point(5, 5));
}

TEST(NPCTest, MoveIgnoresEmptyMap) {
    Bear bear("Baloo", Point(5, 5));
    bear.move(1, 1, 0, 10);
    EXPECT_EQ(bear.getPosition(), Point(5, 5));
}

TEST(NPCTest, ConcurrentMoveAndRead) {
    auto bear = std::make_shared<Bear>("Baloo", Point(50, 50));
    const Rogue rogue("Robin", Point(0, 0));
    {
        const std::jthread mover([bear] {
            for (int i = 0; i < 1000; ++i) {
                bear->move(i % 2 == 0 ? 1 : -1, 0, 100, 100);
            }
        });
        for (int i = 0; i < 1000; ++i) {
            const double distance = bear->distanceTo(rogue);
            EXPECT_GT(distance, 69.0);
        }
    }
    EXPECT_EQ(bear->getPosition(), Point(50, 50));
}
