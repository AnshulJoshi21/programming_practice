#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "termbox2.h"

typedef enum GameState {
  GAME_STATE_TITLE,
  GAME_STATE_CHARACTER_CREATION,
  GAME_STATE_TOWN,
  GAME_STATE_EXPLORE,
  GAME_STATE_COMBAT,
  GAME_STATE_SHOP,
  GAME_STATE_PROFILE

} GameState;

typedef struct GameManager {
  GameState current_state;
  GameState prev_state;
  int selected;
  int menu_size;
  struct tb_event ev;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_run(GameManager *gm);

#endif // GAME_MANAGER_H
