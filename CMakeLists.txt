cmake_minimum_required(VERSION 3.20)
project(aoc-cpp VERSION 0.1.0)

SET(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

find_package(Threads REQUIRED)

add_executable(aoc src/cpp/main.cpp
        src/cpp/days/day01.hpp
        src/cpp/days/day02.hpp
        src/cpp/days/day03.hpp
        src/cpp/days/day04.hpp)

target_link_libraries(aoc
        fmt::fmt
        Threads::Threads)