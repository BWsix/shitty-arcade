cmake_minimum_required(VERSION 3.10)

project(ShittyArcade)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Raylib: https://github.com/raysan5/raylib
find_package(raylib 3.0 REQUIRED)
include_directories(raylib)

# ShittyArcade
include_directories(utils)

include_directories(snake)
add_executable(snake snake/main.c snake/game.c snake/snake.c utils/deque.c)
target_link_libraries(snake raylib)
