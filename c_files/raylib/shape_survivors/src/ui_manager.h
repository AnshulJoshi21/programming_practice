#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "enemies/enemy_manager.h"
#include "player.h"

typedef struct UiManager {
    const Player*       player;
    const EnemyManager* enemy_manager;
} UiManager;

void ui_manager_init(UiManager* ui, const Player* player, const EnemyManager* enemy_manager);
void ui_manager_player_health_bar(const UiManager* ui);
void ui_manager_enemy_health_bar(const UiManager* ui);
void ui_manager_player_xp_bar(const UiManager* ui);

#endif // UI_MANAGER_H
