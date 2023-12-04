#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <chrono>
#include <tuple>
#include <functional>

#include <fmt/core.h>
#include <fmt/color.h>

#include "Input.hpp"
#include "days/day01.hpp"
#include "days/day02.hpp"
#include "days/day04.hpp"

const std::string INPUT_PATH{"res/"};
uint64_t day_count{0};

template<typename T, typename R, typename F>
std::tuple<R, long long> Executor(F func, const T& data) {
    const auto start = std::chrono::high_resolution_clock::now();
    R result = func(data);
    const auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return std::make_tuple(result, elapsed);
}

template<typename T, typename R1, typename R2, typename F1, typename F2>
void Execute(F1 f1, F2 f2, const T& data) {
    auto [result1, elapsed1] = Executor<T, R1>(f1, data);
    auto [result2, elapsed2] = Executor<T, R2>(f2, data);
    fmt::print("Day {} results:\n" , ++day_count);
    fmt::print(fmt::emphasis::bold,
    "\tPart 1: {} finished after {}us\n", result1, elapsed1
);
    fmt::print(fmt::emphasis::bold,
        "\tPart 2: {} finished after {}us\n", result2, elapsed2
    );
}

using namespace aoc;

int main() {
    Execute<std::vector<std::string>,
          std::int64_t, std::int64_t>(
               Day1::Part1, Day1::Part2,
                Input::GetStringData(INPUT_PATH + "day1.txt")
                );

    Execute<std::vector<std::string>,
        std::int64_t, std::int64_t>(
            Day2::Part1, Day2::Part2,
            Input::GetStringData(INPUT_PATH + "day2.txt")
        );

    Execute<std::vector<std::string>,
        std::int64_t, std::int64_t>(
            Day4::Part1, Day4::Part2,
            Input::GetStringData(INPUT_PATH + "day4.txt")
        );
}