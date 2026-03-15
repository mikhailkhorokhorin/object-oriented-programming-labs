#include "solution.hpp"

bool isNotVowel(char c) {
    c = tolower(c);
    return !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

std::string removeVowels(std::string s) {
    std::string res = "";

    for (char c : s)
        if (isNotVowel(c))
            res += c;

    return res;
}
