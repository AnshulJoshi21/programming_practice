#ifndef SHOP_MENU_H
#define SHOP_MENU_H

#include "../game_states.h"
#include <stdbool.h>

void
shop_menu_init(int menu_vertical_padding);
void
shop_menu_draw();
void
shop_menu_update(GameState* current_state);
void
shop_menu_free();

#endif // SHOP_MENU_H