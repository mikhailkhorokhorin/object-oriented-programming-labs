#include "dungeon.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <cstddef>
#include <memory>
#include <mutex>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "bear.hpp"
#include "rogue.hpp"
#include "synced_stream.hpp"
#include "werewolf.hpp"

namespace {

class RecordingObserver final : public IObserver {
public:
    void onEvent(const std::string& message) override {
        const std::lock_guard lock(mutex_);
        messages_.push_back(message);
    }

    std::vector<std::string> messages() const {
        const std::lock_guard lock(mutex_);
        return messages_;
    }

private:
    mutable std::mutex mutex_;
    std::vector<std::string> messages_;
};

Dungeon::Dice sequence(std::vector<int> rolls) {
    auto index = std::make_shared<std::size_t>(0);
    return [rolls = std::move(rolls), index] {
        return rolls[(*index)++ % rolls.size()];
    };
}

constexpr std::size_t QUEUE_CAPACITY = 16;

}

TEST(DungeonTest, RejectsInvalidConfiguration) {
    EXPECT_THROW(Dungeon(0, 10, sequence({1}), QUEUE_CAPACITY), std::invalid_argument);
    EXPECT_THROW(Dungeon(10, 10, nullptr, QUEUE_CAPACITY), std::invalid_argument);
    const Dungeon dungeon(30, 20, sequence({1}), QUEUE_CAPACITY);
    EXPECT_EQ(dungeon.getWidth(), 30);
    EXPECT_EQ(dungeon.getHeight(), 20);
}

TEST(DungeonTest, AttackerWinsOnHigherRoll) {
    Dungeon dungeon(100, 100, sequence({6, 1}), QUEUE_CAPACITY);
    RecordingObserver observer;
    dungeon.addObserver(&observer);
    dungeon.addObserver(nullptr);
    Bear bear("Baloo", Point(0, 0));
    Werewolf werewolf("Lupin", Point(3, 4));
    dungeon.fight(bear, werewolf);
    EXPECT_TRUE(bear.isAlive());
    EXPECT_FALSE(werewolf.isAlive());
    EXPECT_EQ(observer.messages(), std::vector<std::string>{"Baloo killed Lupin"});
}

TEST(DungeonTest, TieDoesNotKill) {
    Dungeon dungeon(100, 100, sequence({3, 3}), QUEUE_CAPACITY);
    Bear bear("Baloo", Point(0, 0));
    Werewolf werewolf("Lupin", Point(1, 1));
    dungeon.fight(bear, werewolf);
    EXPECT_TRUE(werewolf.isAlive());
}

TEST(DungeonTest, DefenderStrikesBack) {
    Dungeon dungeon(100, 100, sequence({6, 1}), QUEUE_CAPACITY);
    RecordingObserver observer;
    dungeon.addObserver(&observer);
    Werewolf werewolf("Lupin", Point(0, 0));
    Bear bear("Baloo", Point(1, 1));
    dungeon.fight(werewolf, bear);
    EXPECT_FALSE(werewolf.isAlive());
    EXPECT_TRUE(bear.isAlive());
    EXPECT_EQ(observer.messages(), std::vector<std::string>{"Baloo killed Lupin"});
}

TEST(DungeonTest, NoFightBeyondKillDistance) {
    Dungeon dungeon(100, 100, sequence({6, 1}), QUEUE_CAPACITY);
    Werewolf werewolf("Lupin", Point(0, 0));
    Rogue rogue("Robin", Point(6, 0));
    dungeon.fight(werewolf, rogue);
    EXPECT_TRUE(rogue.isAlive());
    EXPECT_TRUE(werewolf.isAlive());
}

TEST(DungeonTest, DeadNPCsDoNotFight) {
    Dungeon dungeon(100, 100, sequence({6, 1}), QUEUE_CAPACITY);
    RecordingObserver observer;
    dungeon.addObserver(&observer);
    Bear bear("Baloo", Point(0, 0));
    Werewolf werewolf("Lupin", Point(0, 0));
    werewolf.tryKill();
    dungeon.fight(bear, werewolf);
    bear.tryKill();
    Werewolf other("Other", Point(0, 0));
    dungeon.fight(bear, other);
    EXPECT_TRUE(other.isAlive());
    EXPECT_TRUE(observer.messages().empty());
}

TEST(DungeonTest, FindFightsListsEachPairOnce) {
    Dungeon dungeon(100, 100, sequence({1}), QUEUE_CAPACITY);
    auto bear = std::make_shared<Bear>("Baloo", Point(0, 0));
    auto werewolf = std::make_shared<Werewolf>("Lupin", Point(1, 0));
    auto rogue = std::make_shared<Rogue>("Robin", Point(2, 0));
    auto farBear = std::make_shared<Bear>("Far", Point(90, 90));
    auto deadRogue = std::make_shared<Rogue>("Dead", Point(0, 1));
    deadRogue->tryKill();
    dungeon.addNPC(bear);
    dungeon.addNPC(werewolf);
    dungeon.addNPC(rogue);
    dungeon.addNPC(farBear);
    dungeon.addNPC(deadRogue);
    dungeon.addNPC(nullptr);

    const auto fights = dungeon.findFights();
    ASSERT_EQ(fights.size(), 3U);
    EXPECT_EQ(fights[0], Dungeon::Fight(bear, werewolf));
    EXPECT_EQ(fights[1], Dungeon::Fight(bear, rogue));
    EXPECT_EQ(fights[2], Dungeon::Fight(werewolf, rogue));
}

TEST(DungeonTest, MoveAllKeepsNPCsOnMap) {
    Dungeon dungeon(10, 10, sequence({1}), QUEUE_CAPACITY);
    std::mt19937 engine(3);
    dungeon.spawnRandomNPCs(20, engine);
    for (int step = 0; step < 50; ++step) {
        dungeon.moveAll(engine);
    }
    ASSERT_EQ(dungeon.getAliveNPCs().size(), 20U);
    for (const auto& npc : dungeon.getAliveNPCs()) {
        const Point position = npc->getPosition();
        EXPECT_GE(position.getX(), 0);
        EXPECT_LT(position.getX(), 10);
        EXPECT_GE(position.getY(), 0);
        EXPECT_LT(position.getY(), 10);
    }
}

TEST(DungeonTest, MoveAllStaysWithinMoveDistance) {
    constexpr int MAP_SIZE = 1000;
    constexpr int CENTER = MAP_SIZE / 2;
    Dungeon dungeon(MAP_SIZE, MAP_SIZE, sequence({1}), QUEUE_CAPACITY);
    dungeon.addNPC(std::make_shared<Bear>("Bear", Point(CENTER, CENTER)));
    dungeon.addNPC(std::make_shared<Rogue>("Rogue", Point(CENTER, CENTER)));
    dungeon.addNPC(std::make_shared<Werewolf>("Werewolf", Point(CENTER, CENTER)));
    const auto npcs = dungeon.getAliveNPCs();
    std::mt19937 engine(7);
    for (int step = 0; step < 200; ++step) {
        std::vector<Point> before;
        for (const auto& npc : npcs) {
            before.push_back(npc->getPosition());
        }
        dungeon.moveAll(engine);
        for (std::size_t i = 0; i < npcs.size(); ++i) {
            EXPECT_LE(npcs[i]->getPosition().distanceTo(before[i]), npcs[i]->getMoveDistance());
        }
    }
}

TEST(DungeonTest, PrintMapAndSurvivorsListOnlyAlive) {
    Dungeon dungeon(100, 100, sequence({1}), QUEUE_CAPACITY);
    dungeon.addNPC(std::make_shared<Bear>("Baloo", Point(1, 2)));
    auto dead = std::make_shared<Rogue>("Robin", Point(3, 4));
    dead->tryKill();
    dungeon.addNPC(dead);
    std::ostringstream map;
    dungeon.printMap(map);
    EXPECT_EQ(map.str(), "=== Map (1 alive) ===\nBear Baloo (1, 2)\n");
    std::ostringstream survivors;
    dungeon.printSurvivors(survivors);
    EXPECT_EQ(survivors.str(), "=== Survivors (1) ===\nBear Baloo (1, 2)\n");
}

TEST(DungeonTest, RunKillsNPCsOnSingleCellMap) {
    Dungeon dungeon(1, 1, sequence({6, 1}), 2);
    RecordingObserver observer;
    dungeon.addObserver(&observer);
    dungeon.addNPC(std::make_shared<Bear>("Baloo", Point()));
    dungeon.addNPC(std::make_shared<Werewolf>("Lupin", Point()));
    dungeon.addNPC(std::make_shared<Rogue>("Robin", Point()));
    std::ostringstream out;
    SyncedStream output(out);
    const SimulationTiming timing{std::chrono::milliseconds(300), std::chrono::milliseconds(5),
                                  std::chrono::milliseconds(100)};
    dungeon.run(timing, output);

    EXPECT_EQ(dungeon.getAliveNPCs().size(), 1U);
    EXPECT_EQ(observer.messages().size(), 2U);
    EXPECT_NE(out.str().find("=== Map ("), std::string::npos);
}
