#include "dungeon.hpp"

#include "gtest/gtest.h"

class DummyObserver : public IObserver {
   public:
    std::vector<std::string> messages;
    void onEvent(const std::string& msg) override {
        messages.push_back(msg);
    }
};

TEST(DungeonTest, AddNPCAndPrintAll) {
    Dungeon dungeon(50.0);

    dungeon.addNPC("Bear", "Baloo", 10, 20);
    dungeon.addNPC("Rogue", "Robin", 5, 15);
    dungeon.addNPC("Werewolf", "Lupin", 7, 14);

    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    dungeon.printAll();

    std::cout.rdbuf(oldCout);
    std::string printed = output.str();
    EXPECT_NE(printed.find("Bear Baloo (10, 20)"), std::string::npos);
    EXPECT_NE(printed.find("Rogue Robin (5, 15)"), std::string::npos);
    EXPECT_NE(printed.find("Werewolf Lupin (7, 14)"), std::string::npos);
}

TEST(DungeonTest, BattleKillsNPC) {
    Dungeon dungeon(50.0);
    dungeon.addNPC("Bear", "Baloo", 0, 0);
    dungeon.addNPC("Werewolf", "Lupin", 10, 10);

    DummyObserver observer;
    dungeon.addObserver(&observer);

    dungeon.battle();

    ASSERT_EQ(observer.messages.size(), 1);
    EXPECT_EQ(observer.messages[0], "Baloo killed Lupin");
}

TEST(DungeonTest, SaveAndLoadFromFile) {
    std::remove("test_npcs.txt");

    Dungeon dungeon1(50.0);
    dungeon1.addNPC("Bear", "Baloo", 10, 20);
    dungeon1.addNPC("Rogue", "Robin", 5, 15);

    dungeon1.saveToFile("test_npcs.txt");

    Dungeon dungeon2(50.0);
    dungeon2.loadFromFile("test_npcs.txt");

    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    dungeon2.printAll();
    std::cout.rdbuf(oldCout);
    std::string printed = output.str();

    EXPECT_NE(printed.find("Bear Baloo (10, 20)"), std::string::npos);
    EXPECT_NE(printed.find("Rogue Robin (5, 15)"), std::string::npos);

    std::remove("test_npcs.txt");
}

TEST(DungeonTest, AddUnknownNPC) {
    Dungeon dungeon(50.0);

    std::ostringstream errStream;
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::cerr.rdbuf(errStream.rdbuf());

    dungeon.addNPC("Dragon", "Drako", 0, 0);

    std::cerr.rdbuf(oldCerr);
    std::string errOutput = errStream.str();
    EXPECT_NE(errOutput.find("Unknown NPC type: Dragon"), std::string::npos);
}
