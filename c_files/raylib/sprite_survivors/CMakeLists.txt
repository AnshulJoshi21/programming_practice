cmake_minimum_required(VERSION 3.10)

project(game C)

add_exectable(game src/main.c)

target_compile_features(game PRIVATE c_std_17)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
target_compile_options(game PRIVATE -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)
