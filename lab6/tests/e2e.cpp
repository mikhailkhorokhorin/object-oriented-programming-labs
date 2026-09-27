#include <gtest/gtest.h>

#include "test_support/process.hpp"

TEST(EndToEndTest, MatchesExpectedOutput) {
    const auto inputs = test_support::inputFiles(TEST_DATA_DIR);
    ASSERT_FALSE(inputs.empty());
    for (const auto& input : inputs) {
        const test_support::TempDir workDir;
        auto expected = input;
        expected.replace_extension(".out");
        const auto result = test_support::runProcess(LAB6_MAIN_PATH, {},
                                                     test_support::readFile(input), workDir.path());
        EXPECT_EQ(result.exitCode, 0) << input;
        EXPECT_EQ(result.out, test_support::readFile(expected)) << input;
    }
}

TEST(EndToEndTest, WritesBattleLogToGivenFile) {
    const test_support::TempDir workDir;
    const auto log = workDir.path() / "battle.log";
    const auto result = test_support::runProcess(LAB6_MAIN_PATH, {log.string()},
                                                 "add Bear A 0 0\nadd Werewolf B 1 1\nbattle 5\n");
    EXPECT_EQ(result.exitCode, 0);
    EXPECT_EQ(test_support::readFile(log), "A killed B\n");
}

TEST(EndToEndTest, SavesAndLoadsDungeon) {
    const test_support::TempDir workDir;
    const auto result = test_support::runProcess(
        LAB6_MAIN_PATH, {},
        "add Rogue R 1 2\nsave npcs.txt\nadd Bear B 3 4\nload npcs.txt\nprint\n", workDir.path());
    EXPECT_EQ(result.exitCode, 0);
    EXPECT_EQ(result.out, "Rogue R (1, 2)\n");
}

TEST(EndToEndTest, RejectsInvalidCommands) {
    const test_support::TempDir workDir;
    for (const char* input : {"fly\n", "add Dragon D 1 1\n", "battle\n", "save\n"}) {
        const auto result = test_support::runProcess(LAB6_MAIN_PATH, {}, input, workDir.path());
        EXPECT_EQ(result.exitCode, 1) << input;
        EXPECT_NE(result.err.find("error:"), std::string::npos) << input;
    }
}
