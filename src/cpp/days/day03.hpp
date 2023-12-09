#pragma once

#include <cstdint>
#include <vector>
#include <ranges>
#include <map>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <optional>
#include <set>

namespace aoc::Day3 {

inline auto has_neighbour(const std::vector<std::string>& data,
                        std::size_t i,
                        std::size_t j) -> bool
{
    bool neighbour{false};
    const auto max_i = data.size() - 1;
    const auto max_j = data.at(i).size() - 1;
    if (i > 0) {
        if (data.at(i - 1).at(j) != '.' &&
            !std::isdigit(data.at(i - 1).at(j)))
        {
            neighbour = true;
        }

        if (j > 0 &&
            data.at(i - 1).at(j - 1) != '.' &&
            !std::isdigit(data.at(i - 1).at(j - 1)))
        {
            neighbour = true;
        }

        if (j < max_j &&
            data.at(i - 1).at(j + 1) != '.' &&
            !std::isdigit(data.at(i - 1).at(j + 1))) {
            neighbour = true;
        }
    }

    if (i < max_i) {
        if (j > 0 && data.at(i + 1).at(j - 1) != '.' &&
            !std::isdigit(data.at(i + 1).at(j - 1))) {
            neighbour = true;
        }

        if (data.at(i + 1).at(j) != '.' && !std::isdigit(data.at(i + 1).at(j)))
        {
            neighbour = true;
        }

        if (j < max_j && data.at(i + 1).at(j + 1) != '.' &&
            !std::isdigit(data.at(i + 1).at(j + 1))) {
            neighbour = true;
        }
    }

    if (j < max_j &&
        data.at(i).at(j + 1) != '.'
        && !std::isdigit(data.at(i).at(j + 1))) {
        neighbour = true;
    }

    if (j > 0 &&
        data.at(i).at(j - 1) != '.' &&
        !std::isdigit(data.at(i).at(j - 1))) {
        neighbour = true;
    }
    return neighbour;
}

inline auto gear(const std::vector<std::string>& data,
    std::size_t i,
    std::size_t j) -> std::optional<std::pair<int, int>>
{
    bool neighbour{false};
    const auto max_i = data.size() - 1;
    const auto max_j = data.at(i).size() - 1;
    if (i > 0) {
        if (data.at(i - 1).at(j) == '*')
        {
            return { {i - 1, j} };
        }

        if (j > 0 && data.at(i - 1).at(j - 1) == '*')
        {
            return { {i - 1, j - 1} };
        }

        if (j < max_j && data.at(i - 1).at(j + 1) == '*')
        {
            return { {i - 1, j + 1} };
        }
    }

    if (i < max_i) {
        if (j > 0 && data.at(i + 1).at(j - 1) == '*')
        {
            return { {i + 1, j - 1} };
        }

        if (data.at(i + 1).at(j) == '*')
        {
            return { {i + 1, j} };
        }

        if (j < max_j && data.at(i + 1).at(j + 1) == '*')
        {
            return { {i + 1, j + 1} };
        }
    }

    if (j < max_j && data.at(i).at(j + 1) == '*')
    {
        return { {i, j + 1} };
    }

    if (j > 0 && data.at(i).at(j - 1) == '*')
    {
        return { {i, j - 1} };
    }
    return {};
}


inline auto Part1([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t sum{0};
    std::uint16_t part_number{0};
    bool adjacent{false};
    auto reset_and_add = [&part_number, &sum, &adjacent](){
        if (adjacent) {
            sum += part_number;
        }
        part_number = 0;
        adjacent = false;
    };

    for (std::size_t i{0}; i < data.size(); i++) {
        for (std::size_t j{0}; j < data.at(0).size(); j++) {
            if (std::isdigit(data.at(i).at(j))) {
                part_number *= 10;
                part_number += data.at(i).at(j) - '0';
                adjacent = adjacent || has_neighbour(data, i, j);
                if (j == data.at(i).size() - 1) {
                    reset_and_add();
                }
            }
            else {
                reset_and_add();
            }
        }
    }
    return sum;
}

inline auto Part2([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t sum{0};
    std::uint16_t part_number{0};
    std::map<std::pair<int, int>, std::vector<int>> gears;

    for (std::size_t i{0}; i < data.size(); i++) {
        std::uint16_t part_number{0};
        std::optional<std::pair<int, int>> gear_coord;
        for (std::size_t j{0}; j < data.at(0).size(); j++) {
            if (std::isdigit(data.at(i).at(j))) {
                part_number *= 10;
                part_number += data.at(i).at(j) - '0';
                auto res = gear(data, i, j);
                if (res.has_value()) {
                    gear_coord = res;
                }

                if (j == data.at(i).size() - 1) {
                    if (gear_coord.has_value()) {
                        gears[gear_coord.value()].push_back(part_number);
                    }
                    part_number = 0;
                    gear_coord = {};
                }
            }
            else {
                if (gear_coord.has_value()) {
                    gears[gear_coord.value()].push_back(part_number);
                }
                part_number = 0;
                gear_coord = {};

            }
        }
    }

    for (auto& [k, v] : gears) {
        if (v.size() == 2) {
            sum += v[0] * v[1];
        }
    }

    return sum;
}
}