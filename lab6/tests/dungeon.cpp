#include "dungeon.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "bear.hpp"
#include "test_support/process.hpp"

namespace {

class RecordingObserver final : public IObserver {
public:
    std::vector<std::string> messages;

    void onEvent(const std::string& message) override { messages.push_back(message); }
};

std::string printed(const Dungeon& dungeon) {
    std::ostringstream out;
    dungeon.printAll(out);
    return out.str();
}

}

TEST(DungeonTest, AddAndPrint) {
    Dungeon dungeon;
    EXPECT_TRUE(dungeon.addNPC("Bear", "Baloo", 10, 20));
    EXPECT_TRUE(dungeon.addNPC("Rogue", "Robin", 5, 15));
    EXPECT_TRUE(dungeon.addNPC(std::make_shared<Bear>("Fozzie", Point(0, 500))));
    EXPECT_EQ(printed(dungeon), "Bear Baloo (10, 20)\nRogue Robin (5, 15)\nBear Fozzie (0, 500)\n");
}

TEST(DungeonTest, RejectsUnknownTypeAndOutOfMapPosition) {
    Dungeon dungeon;
    EXPECT_FALSE(dungeon.addNPC("Dragon", "Drako", 0, 0));
    EXPECT_FALSE(dungeon.addNPC("Bear", "Far", 501, 0));
    EXPECT_FALSE(dungeon.addNPC("Bear", "Negative", 0, -1));
    EXPECT_FALSE(dungeon.addNPC(nullptr));
    EXPECT_TRUE(dungeon.getNPCs().empty());
}

TEST(DungeonTest, BattleRemovesKilledNPC) {
    Dungeon dungeon;
    RecordingObserver observer;
    dungeon.addObserver(&observer);
    dungeon.addObserver(nullptr);
    dungeon.addNPC("Bear", "Baloo", 0, 0);
    dungeon.addNPC("Werewolf", "Lupin", 10, 10);

    EXPECT_EQ(dungeon.battle(50.0), 1U);

    ASSERT_EQ(dungeon.getNPCs().size(), 1U);
    EXPECT_EQ(dungeon.getNPCs()[0]->getName(), "Baloo");
    EXPECT_EQ(observer.messages, std::vector<std::string>{"Baloo killed Lupin"});
}

TEST(DungeonTest, DefenderCanKillAttacker) {
    Dungeon dungeon;
    dungeon.addNPC("Bear", "Baloo", 0, 0);
    dungeon.addNPC("Rogue", "Robin", 1, 1);
    EXPECT_EQ(dungeon.battle(5.0), 1U);
    ASSERT_EQ(dungeon.getNPCs().size(), 1U);
    EXPECT_EQ(dungeon.getNPCs()[0]->getName(), "Robin");
}

TEST(DungeonTest, NobodyDiesOutOfRange) {
    Dungeon dungeon;
    RecordingObserver observer;
    dungeon.addObserver(&observer);
    dungeon.addNPC("Bear", "Baloo", 0, 0);
    dungeon.addNPC("Werewolf", "Lupin", 100, 100);
    EXPECT_EQ(dungeon.battle(50.0), 0U);
    EXPECT_EQ(dungeon.getNPCs().size(), 2U);
    EXPECT_TRUE(observer.messages.empty());
}

TEST(DungeonTest, SameTypesDoNotFight) {
    Dungeon dungeon;
    dungeon.addNPC("Bear", "A", 0, 0);
    dungeon.addNPC("Bear", "B", 0, 0);
    EXPECT_EQ(dungeon.battle(10.0), 0U);
    EXPECT_EQ(dungeon.getNPCs().size(), 2U);
}

TEST(DungeonTest, DeadNPCDoesNotFightAgain) {
    Dungeon dungeon;
    RecordingObserver observer;
    dungeon.addObserver(&observer);
    dungeon.addNPC("Werewolf", "Lupin", 0, 0);
    dungeon.addNPC("Bear", "Baloo", 1, 0);
    dungeon.addNPC("Rogue", "Robin", 2, 0);
    EXPECT_EQ(dungeon.battle(10.0), 2U);
    EXPECT_EQ(observer.messages,
              (std::vector<std::string>{"Baloo killed Lupin", "Robin killed Baloo"}));
    ASSERT_EQ(dungeon.getNPCs().size(), 1U);
    EXPECT_EQ(dungeon.getNPCs()[0]->getName(), "Robin");
}

TEST(DungeonTest, SaveAndLoadRoundTrip) {
    const test_support::TempDir dir;
    const auto path = dir.path() / "npcs.txt";
    Dungeon source;
    source.addNPC("Bear", "Baloo", 10, 20);
    source.addNPC("Rogue", "Robin", 5, 15);
    source.saveToFile(path);

    Dungeon target;
    target.addNPC("Werewolf", "Lupin", 1, 1);
    target.loadFromFile(path);
    EXPECT_EQ(printed(target), printed(source));
}

TEST(DungeonTest, LoadRejectsNPCOutsideMap) {
    const test_support::TempDir dir;
    const auto path = dir.path() / "outside.txt";
    test_support::writeFile(path, "Bear Baloo 1 1\nRogue Robin 1000 1000\n");
    Dungeon dungeon;
    dungeon.addNPC("Werewolf", "Lupin", 0, 0);
    EXPECT_THROW(dungeon.loadFromFile(path), std::runtime_error);
    ASSERT_EQ(dungeon.getNPCs().size(), 1U);
    EXPECT_EQ(dungeon.getNPCs()[0]->getName(), "Lupin");
}

TEST(DungeonTest, LoadRejectsMissingOrBrokenFile) {
    const test_support::TempDir dir;
    Dungeon dungeon;
    EXPECT_THROW(dungeon.loadFromFile(dir.path() / "missing.txt"), std::runtime_error);
    EXPECT_THROW(dungeon.saveToFile(dir.path() / "no" / "such" / "dir.txt"), std::runtime_error);
    const auto broken = dir.path() / "broken.txt";
    test_support::writeFile(broken, "Bear Baloo 1 1\n\nDragon Drako 1 1\n");
    dungeon.addNPC("Rogue", "Robin", 0, 0);
    EXPECT_THROW(dungeon.loadFromFile(broken), std::runtime_error);
    EXPECT_EQ(dungeon.getNPCs().size(), 1U);
}
