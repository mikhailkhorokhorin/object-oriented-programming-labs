#include "game.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <sstream>
#include <string>

#include "test_support/process.hpp"

namespace {

std::size_t countOccurrences(const std::string& text, const std::string& pattern) {
    std::size_t count = 0;
    for (auto pos = text.find(pattern); pos != std::string::npos;
         pos = text.find(pattern, pos + 1)) {
        ++count;
    }
    return count;
}

}

TEST(GameTest, DefaultsComeFromConfig) {
    const GameConfig config;
    EXPECT_EQ(config.mapWidth, 100);
    EXPECT_EQ(config.mapHeight, 100);
    EXPECT_EQ(config.npcCount, 50);
    EXPECT_EQ(config.timing.duration, std::chrono::seconds(30));
    EXPECT_EQ(config.timing.printInterval, std::chrono::seconds(1));
}

TEST(GameTest, RunPrintsMapsSurvivorsOnceAndLogsKills) {
    const test_support::TempDir dir;
    GameConfig config;
    config.mapWidth = 3;
    config.mapHeight = 3;
    config.npcCount = 12;
    config.timing = {std::chrono::milliseconds(250), std::chrono::milliseconds(5),
                     std::chrono::milliseconds(100)};
    config.logPath = dir.path() / "log.txt";
    std::ostringstream out;
    Game game(config, out, [roll = 0]() mutable { return roll++ % 2 == 0 ? 6 : 1; });
    EXPECT_EQ(game.getConfig().npcCount, 12);
    game.run();

    const std::string output = out.str();
    EXPECT_GE(countOccurrences(output, "=== Map ("), 2U);
    EXPECT_EQ(countOccurrences(output, "=== Survivors ("), 1U);
    EXPECT_EQ(game.getDungeon().getWidth(), 3);
    const auto alive = game.getDungeon().getAliveNPCs().size();
    EXPECT_LE(alive, 12U);
    EXPECT_NE(output.find("=== Survivors (" + std::to_string(alive) + ") ==="), std::string::npos);
    const std::size_t kills = countOccurrences(output, " killed ");
    EXPECT_EQ(kills, 12U - alive);
    if (kills > 0) {
        EXPECT_EQ(countOccurrences(test_support::readFile(config.logPath), " killed "), kills);
    }
}
