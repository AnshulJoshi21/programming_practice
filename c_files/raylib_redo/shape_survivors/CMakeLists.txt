cmake_minimum_required(VERSION 3.10)

project(game C)

add_executable(game src/main.c src/game_manager.c src/utils.c src/player.c src/systems.c)

target_compile_features(game PRIVATE c_std_17)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
target_link_libraries(game PRIVATE -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)
