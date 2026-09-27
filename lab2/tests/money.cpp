#include "money.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

TEST(MoneyTest, DefaultIsZero) {
    const Money money;
    EXPECT_EQ(money.getSize(), 1U);
    EXPECT_EQ(money.toString(), "0.00");
    EXPECT_TRUE(Money::equals(money, Money("0.00")));
}

TEST(MoneyTest, StringConstructorStoresDigitsLeastSignificantFirst) {
    const Money money("123.45");
    EXPECT_EQ(money.getDigits(), (std::vector<unsigned char>{5, 4, 3, 2, 1}));
    EXPECT_EQ(money.toString(), "123.45");
}

TEST(MoneyTest, StringConstructorAcceptsEmptyRubles) {
    EXPECT_EQ(Money(".07").toString(), "0.07");
}

TEST(MoneyTest, StringConstructorDropsLeadingZeros) {
    const Money money("000.50");
    EXPECT_EQ(money.getSize(), 2U);
    EXPECT_TRUE(Money::equals(money, Money("0.50")));
}

TEST(MoneyTest, StringConstructorRejectsInvalidInput) {
    EXPECT_THROW(Money("12.3"), std::invalid_argument);
    EXPECT_THROW(Money("abc.de"), std::invalid_argument);
    EXPECT_THROW(Money("12,34"), std::invalid_argument);
    EXPECT_THROW(Money("-1.00"), std::invalid_argument);
    EXPECT_THROW(Money("1.2x"), std::invalid_argument);
    EXPECT_THROW(Money("\xC3\xA9.00"), std::invalid_argument);
}

TEST(MoneyTest, DoubleConstructorRoundsToKopecks) {
    EXPECT_TRUE(Money::equals(Money(678.90), Money("678.90")));
    EXPECT_TRUE(Money::equals(Money(0.0), Money()));
}

TEST(MoneyTest, DoubleConstructorRejectsInvalidValues) {
    EXPECT_THROW(Money(-1.23), std::invalid_argument);
    EXPECT_THROW(Money(std::numeric_limits<double>::quiet_NaN()), std::invalid_argument);
    EXPECT_THROW(Money(std::numeric_limits<double>::infinity()), std::invalid_argument);
    EXPECT_THROW(Money(1e300), std::out_of_range);
}

TEST(MoneyTest, ToDoubleOfSmallAmountIsInRubles) {
    EXPECT_DOUBLE_EQ(Money(0.05).toDouble(), 0.05);
    EXPECT_DOUBLE_EQ(Money("1234.56").toDouble(), 1234.56);
}

TEST(MoneyTest, CopyAssignmentMakesIndependentCopy) {
    Money target("1.00");
    const Money source("56.78");
    target = source;
    EXPECT_TRUE(Money::equals(target, source));
    target = Money::add(target, Money("1.00"));
    EXPECT_EQ(source.toString(), "56.78");
    EXPECT_EQ(target.toString(), "57.78");
}

TEST(MoneyTest, SelfAssignmentKeepsValue) {
    Money money("12.34");
    Money& alias = money;
    money = alias;
    EXPECT_EQ(money.toString(), "12.34");
}

TEST(MoneyTest, MoveKeepsValue) {
    Money source("9.99");
    const Money moved(std::move(source));
    EXPECT_EQ(moved.toString(), "9.99");
    Money target;
    target = Money("3.50");
    EXPECT_EQ(target.toString(), "3.50");
}

TEST(MoneyTest, AddWithCarry) {
    EXPECT_TRUE(Money::equals(Money::add(Money("100.50"), Money("200.75")), Money("301.25")));
    EXPECT_TRUE(Money::equals(Money::add(Money("99.99"), Money("0.01")), Money("100.00")));
}

TEST(MoneyTest, AddResultHasNoLeadingZeros) {
    const Money sum = Money::add(Money("0.50"), Money("0.50"));
    EXPECT_EQ(sum.getSize(), 3U);
    EXPECT_TRUE(Money::equals(sum, Money("1.00")));
    EXPECT_FALSE(Money::greater(sum, Money("1.00")));
}

TEST(MoneyTest, SubtractWithBorrow) {
    EXPECT_TRUE(Money::equals(Money::subtract(Money("500.25"), Money("100.26")), Money("399.99")));
}

TEST(MoneyTest, SubtractResultHasNoLeadingZeros) {
    const Money diff = Money::subtract(Money("100.00"), Money("99.99"));
    EXPECT_EQ(diff.getSize(), 1U);
    EXPECT_TRUE(Money::equals(diff, Money("0.01")));
    EXPECT_TRUE(Money::less(diff, Money("0.02")));
    EXPECT_TRUE(Money::equals(Money::subtract(Money("7.00"), Money("7.00")), Money()));
}

TEST(MoneyTest, SubtractNegativeThrows) {
    EXPECT_THROW(Money::subtract(Money("10.00"), Money("20.00")), std::invalid_argument);
}

TEST(MoneyTest, Comparisons) {
    const Money small("10.00");
    const Money large("20.00");
    const Money sameLength("19.99");
    EXPECT_TRUE(Money::less(small, large));
    EXPECT_TRUE(Money::greater(large, small));
    EXPECT_TRUE(Money::greater(large, sameLength));
    EXPECT_FALSE(Money::greater(small, small));
    EXPECT_TRUE(Money::lessOrEqual(small, large));
    EXPECT_TRUE(Money::lessOrEqual(small, small));
    EXPECT_FALSE(Money::lessOrEqual(large, small));
    EXPECT_TRUE(Money::greaterOrEqual(large, small));
    EXPECT_TRUE(Money::greaterOrEqual(small, small));
    EXPECT_FALSE(Money::greaterOrEqual(small, large));
    EXPECT_TRUE(Money::notEquals(small, large));
    EXPECT_FALSE(Money::notEquals(small, Money("10.00")));
}

TEST(MoneyTest, PrintUsesSeparator) {
    std::ostringstream out;
    Money("123.45").print(out);
    Money("678.90").print(out, ',');
    Money("0.05").print(out);
    EXPECT_EQ(out.str(), "123.45\n678,90\n0.05\n");
}
