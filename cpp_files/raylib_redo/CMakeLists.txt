cmake_minimum_required(VERSION 3.15)

project(game C++)

add_executable(game)

target_compile_features(game PRIVATE c++_std_20)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
target_link_libraries(game PRIVATE raylib GL m pthread dl rt X11)
