#pragma once

#include <cstdint>
#include <vector>
#include <ranges>
#include <string_view>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

namespace aoc::Day3 {

inline auto view_to_vec(std::string_view& v) -> std::vector<int> {
    std::vector<int> numbers;
    for (auto token : std::views::split(v, ' ')) {
        auto tv = std::string_view(token);
        tv.remove_prefix(std::min(tv.find_first_not_of(" "), tv.size()));
        int number{ 0 };

        auto [ptr, ec] = std::from_chars(tv.data(), tv.data() + tv.size(), number);

        if (ec == std::errc())
            numbers.push_back(number);
    }
    std::sort(numbers.begin(), numbers.end());
    return numbers;
    };

inline auto Part1([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t sum{0};
    using std::operator""sv;
    constexpr auto delim{" "sv };

    for (const auto& line : data) {
        auto left_view = std::string_view(line.begin() + line.rfind(':') + 2, line.begin() + line.rfind('|'));
        auto elf_numbers = view_to_vec(left_view);

        auto right_view = std::string_view(line.begin() + line.rfind('|') + 2, line.end());
        auto my_numbers = view_to_vec(right_view);

        std::vector<int> diff;
        std::set_intersection(elf_numbers.begin(), elf_numbers.end(),
                            my_numbers.begin(), my_numbers.end(),
                            std::inserter(diff, diff.begin()));

        if (!diff.empty()) sum += std::pow(2, diff.size() - 1);
    }
    return sum;
}

inline auto Part2([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t sum{0};
    using std::operator""sv;
    constexpr auto delim{ " "sv };

    std::vector<int> count(data.size(), 1);
    int i{0};
    for (const auto& line : data) {
        auto left_view = std::string_view(line.begin() + line.rfind(':') + 2, line.begin() + line.rfind('|'));
        auto elf_numbers = view_to_vec(left_view);

        auto right_view = std::string_view(line.begin() + line.rfind('|') + 2, line.end());
        auto my_numbers = view_to_vec(right_view);

        std::vector<int> diff;
        std::set_intersection(elf_numbers.begin(), elf_numbers.end(),
            my_numbers.begin(), my_numbers.end(),
            std::inserter(diff, diff.begin()));


        for (int j = i + 1; j <= i + diff.size(); j++) {
            count[j] += count[i];
        }
        i++;
    }
    sum = std::accumulate(count.begin(), count.end(), 0);
    return sum;
}
}
