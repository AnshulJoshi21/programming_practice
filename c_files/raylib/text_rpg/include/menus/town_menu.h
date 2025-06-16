#ifndef TOWN_MENU_H
#define TOWN_MENU_H

#include "../game_states.h"
#include <stdbool.h>

void
town_menu_init(int menu_vertical_padding);
void
town_menu_draw();
void
town_menu_update(GameState *current_state);
void
town_menu_free();

#endif // TOWN_MENU_H