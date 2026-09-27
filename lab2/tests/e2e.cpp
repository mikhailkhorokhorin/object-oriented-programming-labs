#include <gtest/gtest.h>

#include "test_support/process.hpp"

TEST(EndToEndTest, MatchesExpectedOutput) {
    const auto inputs = test_support::inputFiles(TEST_DATA_DIR);
    ASSERT_FALSE(inputs.empty());
    for (const auto& input : inputs) {
        auto expected = input;
        expected.replace_extension(".out");
        const auto result =
            test_support::runProcess(LAB2_MAIN_PATH, {}, test_support::readFile(input));
        EXPECT_EQ(result.exitCode, 0) << input;
        EXPECT_EQ(result.out, test_support::readFile(expected)) << input;
    }
}

TEST(EndToEndTest, RejectsUnpairedAmount) {
    const auto result = test_support::runProcess(LAB2_MAIN_PATH, {}, "1.00 2.00\n3.00\n");
    EXPECT_EQ(result.exitCode, 1);
    EXPECT_EQ(result.out, "1.00 + 2.00 = 3.00\n1.00 < 2.00\n");
    EXPECT_NE(result.err.find("missing second amount after 3.00"), std::string::npos);
}

TEST(EndToEndTest, RejectsInvalidAmount) {
    const auto result = test_support::runProcess(LAB2_MAIN_PATH, {}, "1.5 2.00\n");
    EXPECT_EQ(result.exitCode, 1);
    EXPECT_NE(result.err.find("error:"), std::string::npos);
}
