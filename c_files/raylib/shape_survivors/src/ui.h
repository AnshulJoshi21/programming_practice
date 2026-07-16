#ifndef UI_H
#define UI_H

#include "enemies/enemy_manager.h"
#include "player.h"

void ui_draw_health_bars(const Player* player, const EnemyManager* enemy_manager);
void ui_draw_player_exp_bar(const Player* player);

#endif // UI_H
