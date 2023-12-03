#pragma once

#include <cstdint>
#include <vector>
#include <ranges>
#include <string_view>

namespace aoc::Day2 {

inline auto Part1([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t sum{0};
    using std::operator""sv;
    constexpr auto delim = ";"sv;
    std::uint64_t game_number{1};
    for (const auto& line : data) {
        bool possible{true};
        auto game = std::string_view(line.begin() + line.rfind(':') + 1, line.end());
        constexpr std::uint64_t red_max{12}, green_max{13}, blue_max{14};

        for (const auto word : std::views::split(game, delim)) {
            auto segment = std::string_view(word);
            for (auto tok : std::views::split(segment, ',')) {
                std::uint64_t number{0};
                auto view = std::string_view(tok);
                std::from_chars(view.data() + 1, view.data() + view.size(), number);

                if (view.contains("red"sv)) if (number > red_max) possible = false;
                if (view.contains("green"sv)) if (number > green_max) possible = false;
                if (view.contains("blue"sv)) if (number > blue_max) possible = false;
            }
        }

        if (possible) {
            sum += game_number;
        }

        game_number++;
    }
    return sum;
}

inline auto Part2([[maybe_unused]] const std::vector<std::string>& data) -> std::uint64_t {
    std::uint64_t sum{0};

    using std::operator""sv;
    constexpr auto delim = ";"sv;
    for (const auto& line : data) {
        auto game = std::string_view(line.begin() + line.rfind(':') + 1, line.end());
        std::uint64_t red{0}, green{0}, blue{0};
        for (const auto word : std::views::split(game, delim)) {
            auto segment = std::string_view(word);
            for (auto tok : std::views::split(segment, ',')) {
                std::uint64_t number{0};
                auto view = std::string_view(tok);
                std::from_chars(view.data() + 1, view.data() + view.size(), number);

                if (view.contains("red"sv)) red = std::max(number, red);
                if (view.contains("green"sv)) green = std::max(number, green);
                if (view.contains("blue"sv)) blue = std::max(number, blue);
            }
        }

        sum += red * green * blue;
    }
    return sum;
}
}
