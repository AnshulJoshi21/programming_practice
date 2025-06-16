#ifndef MAP_MENU_H
#define MAP_MENU_H

#include "../game_states.h"
#include <stdbool.h>

void
map_menu_init(int menu_vertical_padding);
void
map_menu_draw();
void
map_menu_update(GameState* current_state);
void
map_menu_free();

#endif // MAP_MENU_H