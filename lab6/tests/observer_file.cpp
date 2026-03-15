#include "observer_file.hpp"

#include "gtest/gtest.h"

TEST(FileLoggerTest, OnEventWritesToFile) {
    std::remove("log.txt");

    FileLogger fileLogger;

    fileLogger.onEvent("Test event message 1");
    fileLogger.onEvent("Test event message 2");

    std::ifstream file("log.txt");
    ASSERT_TRUE(file.is_open());

    std::string line1;
    std::getline(file, line1);
    EXPECT_EQ(line1, "Test event message 1");

    std::string line2;
    std::getline(file, line2);
    EXPECT_EQ(line2, "Test event message 2");

    file.close();
    std::remove("log.txt");
}
