#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <map>

namespace aoc::Day1 {

inline auto Part1([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    const std::string numbers{"0123456789"};
    std::uint64_t sum{0};
    for (const auto& s : data) {
        auto first = s.find_first_of(numbers);
        auto last = s.find_last_of(numbers);

        sum += (s.at(first) - '0') * 10 + (s.at(last) - '0');
    }
    return sum;
}

void replaceNumbers(std::string &str) {
    std::unordered_map<std::string, char> numMap = {
        {"one", '1'}, {"two", '2'}, {"three", '3'},
        {"four", '4'}, {"five", '5'}, {"six", '6'},
        {"seven", '7'}, {"eight", '8'}, {"nine", '9'}
    };

    size_t firstNumPos = std::string::npos;
    size_t lastNumPos = std::string::npos;

    for (size_t i = 0; i < str.size(); ++i) {
        if (std::isdigit(str[i])) {
            if (firstNumPos == std::string::npos) {
                firstNumPos = i;
            }
            lastNumPos = i;
        } else {
            for (const auto &pair : numMap) {
                if (i + pair.first.size() <= str.size() && str.substr(i, pair.first.size()) == pair.first) {
                    if (firstNumPos == std::string::npos) {
                        firstNumPos = i;
                        str.replace(i, pair.first.size(), 1, pair.second);
                        i++; // Increment to skip over the digit just inserted
                        break;
                    } else {
                        lastNumPos = i;
                    }
                }
            }
        }
    }

    if (lastNumPos != std::string::npos && lastNumPos != firstNumPos) {
        for (const auto &pair : numMap) {
            if (lastNumPos + pair.first.size() <= str.size() && str.substr(lastNumPos, pair.first.size()) == pair.first) {
                str.replace(lastNumPos, pair.first.size(), 1, pair.second);
                break;
            }
        }
    }
}

inline auto Part2([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {

    const std::string numbers{"0123456789"};
    std::uint64_t sum{0};
    for (const auto& s : data) {
        auto input = s;
        replaceNumbers(input);
        auto first = input.find_first_of(numbers);
        auto last = input.find_last_of(numbers);
        sum += (input.at(first) - '0') * 10 + (input.at(last) - '0');
    }

    return sum;
}
}
