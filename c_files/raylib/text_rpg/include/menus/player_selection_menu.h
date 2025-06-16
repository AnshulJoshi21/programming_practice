#ifndef PLAYER_SELECTION_MENU_H
#define PLAYER_SELECTION_MENU_H

#include "../game_states.h"
#include <stdbool.h>

typedef struct Player Player;

void
player_selection_init(int menu_vertical_padding);
void
player_selection_draw();
Player
player_selection_update(GameState* current_state, bool* player_selected);
void
player_selection_free();

#endif // PLAYER_SELECTION_MENU_H