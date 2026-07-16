cmake_minimum_required(VERSION 3.15)

project(game LANGUAGES C)

add_executable(game
  src/animation_data.c
  src/asset_manager.c
  src/game_manager.c
  src/main.c
  src/player.c
  src/systems.c
  src/utils.c
)

target_compile_features(game PRIVATE c_std_17)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
target_link_libraries(game PRIVATE raylib GL m pthread dl rt X11)

