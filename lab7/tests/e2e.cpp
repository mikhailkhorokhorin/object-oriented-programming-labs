#include <gtest/gtest.h>

#include <string>

#include "test_support/process.hpp"

TEST(EndToEndTest, RunsForGivenSecondsAndPrintsSurvivorsOnce) {
    const test_support::TempDir workDir;
    const auto result = test_support::runProcess(LAB7_MAIN_PATH, {"1"}, "", workDir.path());
    EXPECT_EQ(result.exitCode, 0);
    EXPECT_NE(result.out.find("=== Map ("), std::string::npos);
    const auto first = result.out.find("=== Survivors (");
    ASSERT_NE(first, std::string::npos);
    EXPECT_EQ(result.out.find("=== Survivors (", first + 1), std::string::npos);
}

TEST(EndToEndTest, RejectsInvalidDuration) {
    const test_support::TempDir workDir;
    for (const char* duration : {"soon", "2abc", "0", "-1", ""}) {
        const auto result =
            test_support::runProcess(LAB7_MAIN_PATH, {duration}, "", workDir.path());
        EXPECT_EQ(result.exitCode, 1) << duration;
        EXPECT_NE(result.err.find("error: duration must be a positive number of seconds"),
                  std::string::npos)
            << duration;
    }
}
