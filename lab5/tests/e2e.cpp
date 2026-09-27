#include <gtest/gtest.h>

#include "test_support/process.hpp"

TEST(EndToEndTest, MatchesExpectedOutput) {
    const auto inputs = test_support::inputFiles(TEST_DATA_DIR);
    ASSERT_FALSE(inputs.empty());
    for (const auto& input : inputs) {
        auto expected = input;
        expected.replace_extension(".out");
        const auto result =
            test_support::runProcess(LAB5_MAIN_PATH, {}, test_support::readFile(input));
        EXPECT_EQ(result.exitCode, 0) << input;
        EXPECT_EQ(result.out, test_support::readFile(expected)) << input;
    }
}
