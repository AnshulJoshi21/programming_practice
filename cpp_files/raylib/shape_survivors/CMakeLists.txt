cmake_minimum_required(VERSION 3.15)

project(game LANGUAGES CXX)

add_executable(game
src/bullets/bullet.cpp
src/bullets/bullet_manager.cpp
src/collision_manager.cpp
src/drops/drop.cpp
src/drops/drop_manager.cpp
src/enemies/enemy.cpp
src/enemies/enemy_manager.cpp
src/game_manager.cpp
src/main.cpp
src/player.cpp
src/systems.cpp
src/ui_manager.cpp
src/upgrade_manager.cpp
src/utils.cpp
)

target_compile_features(game PRIVATE cxx_std_20)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
target_link_libraries(game PRIVATE raylib GL m pthread dl rt X11)
