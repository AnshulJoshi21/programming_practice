cmake_minimum_required(VERSION 3.15)

project(game LANGUAGES CXX)

add_executable(game
  src/main.cpp 
  src/game_manager.cpp
  src/player.cpp
  src/utils.cpp
  src/enemies/enemy.cpp
  src/enemies/enemy_manager.cpp
)

target_compile_features(game PRIVATE cxx_std_20)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
target_link_libraries(game PRIVATE raylib GL m pthread dl rt X11)
