#define TB_IMPL
#include "game_manager.h"

int main(void) {
  GameManager game_manager;
  game_manager_init(&game_manager);

  game_manager_run(&game_manager);

  return 0;
}
