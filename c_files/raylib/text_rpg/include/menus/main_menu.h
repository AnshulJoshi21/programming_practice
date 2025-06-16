#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../game_states.h"
#include <stdbool.h>

void
main_menu_init(int menu_vertical_padding);
void
main_menu_draw();
void
main_menu_update(GameState *current_state, bool player_selected);
void
main_menu_free();

#endif // MAIN_MENU_H