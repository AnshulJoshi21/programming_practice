cmake_minimum_required(VERSION 3.15)

project(game C)

add_executable(game
  src/main.c
  src/game_manager.c
  src/player.c
  src/timer.c
  src/utils.c
  src/enemies/enemy_data.c
  src/enemies/enemy.c
  src/enemies/enemy_manager.c
  src/bullets/bullet_projectile.c
  src/bullets/bullet_orbital.c
  src/bullets/bullet_manager.c
)

# set(SANITIZERS -fsanitize=address,undefined)

target_compile_features(game PRIVATE c_std_17)
target_compile_options(game PRIVATE -Wall -Wextra -O2)
target_link_options(game PRIVATE ${SANITIZERS})
target_link_libraries(game PRIVATE -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)
