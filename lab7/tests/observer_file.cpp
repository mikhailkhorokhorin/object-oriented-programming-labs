#include "observer_file.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "test_support/process.hpp"

TEST(FileLoggerTest, AppendsEventsToConfiguredFile) {
    const test_support::TempDir dir;
    const auto path = dir.path() / "battle.log";
    FileLogger logger(path);
    EXPECT_EQ(logger.getPath(), path);
    logger.onEvent("first");
    logger.onEvent("second");
    EXPECT_EQ(test_support::readFile(path), "first\nsecond\n");
}

TEST(FileLoggerTest, DefaultPathIsLogTxt) {
    const FileLogger logger;
    EXPECT_EQ(logger.getPath(), "log.txt");
}

TEST(FileLoggerTest, ConcurrentEventsAreAllWritten) {
    const test_support::TempDir dir;
    const auto path = dir.path() / "battle.log";
    FileLogger logger(path);
    {
        std::vector<std::jthread> threads;
        for (int t = 0; t < 4; ++t) {
            threads.emplace_back([&logger] {
                for (int i = 0; i < 50; ++i) {
                    logger.onEvent("event");
                }
            });
        }
    }
    std::istringstream in(test_support::readFile(path));
    std::string line;
    int lines = 0;
    while (std::getline(in, line)) {
        EXPECT_EQ(line, "event");
        ++lines;
    }
    EXPECT_EQ(lines, 200);
}
