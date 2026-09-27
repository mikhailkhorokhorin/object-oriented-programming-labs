#include "solution.hpp"

#include <cctype>

bool isNotVowel(char c) {
    const int lower = std::tolower(static_cast<unsigned char>(c));
    return !(lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u');
}

std::string removeVowels(std::string_view text) {
    std::string result;
    result.reserve(text.size());
    for (const char c : text) {
        if (isNotVowel(c)) {
            result += c;
        }
    }
    return result;
}
