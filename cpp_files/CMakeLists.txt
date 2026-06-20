cmake_minimum_required(VERSION 3.16)

project(game VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game)

target_sources(game PRIVATE # add sources = main.c ...)

target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
