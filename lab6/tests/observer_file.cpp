#include "observer_file.hpp"

#include <gtest/gtest.h>

#include "test_support/process.hpp"

TEST(FileLoggerTest, AppendsEventsToConfiguredFile) {
    const test_support::TempDir dir;
    const auto path = dir.path() / "battle.log";
    FileLogger logger(path);
    EXPECT_EQ(logger.getPath(), path);
    logger.onEvent("Test event message 1");
    logger.onEvent("Test event message 2");
    EXPECT_EQ(test_support::readFile(path), "Test event message 1\nTest event message 2\n");

    FileLogger reopened(path);
    reopened.onEvent("Test event message 3");
    EXPECT_EQ(test_support::readFile(path),
              "Test event message 1\nTest event message 2\nTest event message 3\n");
}

TEST(FileLoggerTest, DefaultPathIsLogTxt) {
    const FileLogger logger;
    EXPECT_EQ(logger.getPath(), "log.txt");
}
