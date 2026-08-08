cmake_minimum_required(VERSION 3.20)

project(game C)

add_executable(game src/main.c)

target_compile_features(game PRIVATE c_std_17)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2 -fsanitize=adress)
