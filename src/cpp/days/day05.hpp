#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <map>

namespace aoc::Day5 {

struct Map {
    std::uint64_t dst; 
    std::uint64_t src;
    std::uint64_t offset;
};

inline auto get_seeds(const std::string s) -> std::vector<std::uint64_t> {
    using std::operator""sv;
    std::vector<std::uint64_t> seeds;
    std::uint64_t seed{0};
    for (const auto token : std::views::split(s, " "sv)) {
        auto view = std::string_view(token);
        auto [ptr, ec] = std::from_chars(view.data(), view.data() + view.size(), seed);
        if (seed != 0) seeds.push_back(seed);
    }
    return seeds;
}

inline auto get_almanac(const std::vector<std::string>& data) -> std::array<std::vector<Map>, 7> {
    using std::operator""sv;
    std::array<std::vector<Map>, 7> almanac;
    std::size_t current_map{0};
    for (std::size_t i{2}; i < data.size(); i++) {
        if (data[i].empty()) {
            current_map++;
        }

        if (!std::isdigit(data[i][0])) continue;

        std::vector<std::uint64_t> entries;
        std::uint64_t number{0};
        for (const auto token : std::views::split(data[i], " "sv)) {
            auto view = std::string_view(token);
            auto [ptr, ec] = std::from_chars(view.data(), view.data() + view.size(), number);
            entries.push_back(number);
        }
        almanac[current_map].push_back({entries[0], entries[1], entries[2]});
    }
    return almanac;
}

inline auto Part1([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t min = std::numeric_limits<int64_t>::max();
    std::vector<std::uint64_t> seeds{get_seeds(data[0])};
    std::array<std::vector<Map>, 7> almanac{get_almanac(data)};
    for (auto& location : seeds) {
        for (std::size_t i{0}; i < almanac.size(); i++) {
            const auto& map = almanac[i];
            for (std::size_t j{0}; j < map.size(); j++) {
                if (map[j].src <= location && location < map[j].src + map[j].offset) {
                    location = map[j].dst + (location - map[j].src);
                    break;
                }
            }
        }
        min = std::min(location, min);
    }
    return min;
}

inline auto Part2([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t min = std::numeric_limits<int64_t>::max();
    std::vector<std::uint64_t> seeds{get_seeds(data[0])};
    std::array<std::vector<Map>, 7> almanac{get_almanac(data)};

    for (size_t seed{0}; seed < seeds.size(); seed += 2) {
        auto start = seeds[seed];
        auto end = start + seeds[seed + 1];
        while (start < end) {
            auto location = start;
            for (std::size_t i{0}; i < almanac.size(); i++) {
                const auto& map = almanac[i];
                for (std::size_t j{0}; j < map.size(); j++) {
                    if (map[j].src <= location && location < map[j].src + map[j].offset) {
                        location = map[j].dst + (location - map[j].src);
                        break;
                    }
                }
            }
            min = std::min(location, min);
            start++;
        }
    }
    return min;
}
}
