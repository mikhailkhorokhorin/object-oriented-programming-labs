#include <gtest/gtest.h>

#include "money.hpp"

TEST(MoneyTest, DefaultConstructor) {
    Money m;
    EXPECT_EQ(m.getSize(), 1);
    EXPECT_EQ(m.toDouble(), 0.0);
}

TEST(MoneyTest, StringConstructorValid) {
    Money m("123.45");
    EXPECT_EQ(m.toString(), "123.45");
    EXPECT_DOUBLE_EQ(m.toDouble(), 123.45);
}

TEST(MoneyTest, DoubleConstructorValid) {
    Money m(678.90);
    EXPECT_DOUBLE_EQ(m.toDouble(), 678.90);
    EXPECT_EQ(m.toString(), "678.90");
}

TEST(MoneyTest, CopyConstructor) {
    Money a("12.34");
    Money b(a);
    EXPECT_TRUE(Money::equals(a, b));
}

TEST(MoneyTest, CopyMethod) {
    Money a("56.78");
    Money b = Money::copy(a);
    EXPECT_TRUE(Money::equals(a, b));
}

TEST(MoneyTest, AddMoney) {
    Money a("100.50");
    Money b("200.75");
    Money c = Money::add(a, b);
    EXPECT_DOUBLE_EQ(c.toDouble(), 301.25);
}

TEST(MoneyTest, SubtractMoney) {
    Money a("500.25");
    Money b("100.25");
    Money c = Money::subtract(a, b);
    EXPECT_DOUBLE_EQ(c.toDouble(), 400.0);
}

TEST(MoneyTest, SubtractNegativeThrows) {
    Money a("10.00");
    Money b("20.00");
    EXPECT_THROW(Money::subtract(a, b), std::invalid_argument);
}

TEST(MoneyTest, EqualsNotEquals) {
    Money a("12.34");
    Money b("12.34");
    Money c("23.45");
    EXPECT_TRUE(Money::equals(a, b));
    EXPECT_FALSE(Money::equals(a, c));
    EXPECT_TRUE(Money::notEquals(a, c));
    EXPECT_FALSE(Money::notEquals(a, b));
}

TEST(MoneyTest, GreaterLess) {
    Money a("10.00");
    Money b("20.00");
    EXPECT_TRUE(Money::less(a, b));
    EXPECT_TRUE(Money::greater(b, a));
    EXPECT_TRUE(Money::lessOrEqual(a, b));
    EXPECT_TRUE(Money::greaterOrEqual(b, a));
    EXPECT_TRUE(Money::greaterOrEqual(a, a));
}

TEST(MoneyTest, PrintMethod) {
    Money m("123.45");

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    m.print();

    std::cout.rdbuf(oldCout);
    EXPECT_EQ(oss.str(), "123.45\n");
}

TEST(MoneyTest, PrintMethodWithComma) {
    Money m("678.90");

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    m.print(',');

    std::cout.rdbuf(oldCout);
    EXPECT_EQ(oss.str(), "678,90\n");
}

TEST(MoneyTest, ParseStringInvalidFormat) {
    EXPECT_THROW(Money("12.3"), std::invalid_argument);
    EXPECT_THROW(Money("abc.def"), std::invalid_argument);
    EXPECT_THROW(Money("12,34"), std::invalid_argument);
}

TEST(MoneyTest, ParseDoubleNegative) {
    EXPECT_THROW(Money(-1.23), std::invalid_argument);
}

TEST(MoneyTest, ToStringToDoubleConsistency) {
    Money m("1234.56");
    double value = m.toDouble();
    std::string str = m.toString();
    Money n(value);
    EXPECT_EQ(str, n.toString());
    EXPECT_DOUBLE_EQ(value, n.toDouble());
}
