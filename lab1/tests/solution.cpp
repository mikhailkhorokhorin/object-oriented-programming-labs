#include "solution.hpp"

#include <gtest/gtest.h>

TEST(IsNotVowelTest, LowercaseVowels) {
    EXPECT_FALSE(isNotVowel('a'));
    EXPECT_FALSE(isNotVowel('e'));
    EXPECT_FALSE(isNotVowel('i'));
    EXPECT_FALSE(isNotVowel('o'));
    EXPECT_FALSE(isNotVowel('u'));
}

TEST(IsNotVowelTest, UppercaseVowels) {
    EXPECT_FALSE(isNotVowel('A'));
    EXPECT_FALSE(isNotVowel('E'));
    EXPECT_FALSE(isNotVowel('I'));
    EXPECT_FALSE(isNotVowel('O'));
    EXPECT_FALSE(isNotVowel('U'));
}

TEST(IsNotVowelTest, Consonants) {
    EXPECT_TRUE(isNotVowel('b'));
    EXPECT_TRUE(isNotVowel('C'));
    EXPECT_TRUE(isNotVowel('z'));
    EXPECT_TRUE(isNotVowel('Y'));
}

TEST(IsNotVowelTest, NonAlphabetic) {
    EXPECT_TRUE(isNotVowel('1'));
    EXPECT_TRUE(isNotVowel(' '));
    EXPECT_TRUE(isNotVowel('#'));
}

TEST(RemoveVowelsTest, EmptyString) {
    EXPECT_EQ(removeVowels(""), "");
}

TEST(RemoveVowelsTest, OnlyVowels) {
    EXPECT_EQ(removeVowels("aeiouAEIOU"), "");
}

TEST(RemoveVowelsTest, NoVowels) {
    EXPECT_EQ(removeVowels("bcdfg"), "bcdfg");
}

TEST(RemoveVowelsTest, MixedString) {
    EXPECT_EQ(removeVowels("Hello World"), "Hll Wrld");
    EXPECT_EQ(removeVowels("Moscow Aviation Insitute"), "Mscw vtn nstt");
    EXPECT_EQ(removeVowels("This website is for LOL!"), "Ths wbst s fr LL!");
}

TEST(RemoveVowelsTest, NonAlphabeticCharacters) {
    EXPECT_EQ(removeVowels("123!@#"), "123!@#");
    EXPECT_EQ(removeVowels("a1e2i3o4u5"), "12345");
}
