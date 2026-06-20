cmake_minimum_required(VERSION 3.15)

project(game C)

add_executable(game

src/bullets/bullet.c
src/bullets/bullet_manager.c
src/collision_manager.c
src/drops/drop.c
src/drops/drop_manager.c
src/enemies/enemy.c
src/enemies/enemy_manager.c
src/game_manager.c
src/main.c
src/player.c
src/systems.c
src/utils.c)

target_compile_features(game PRIVATE c_std_17)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -O2)
target_link_libraries(game PRIVATE raylib GL m pthread dl rt X11)
