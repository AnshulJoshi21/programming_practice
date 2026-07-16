#pragma once

#include "enemies/enemy_manager.hpp"
#include "player.hpp"

class UiManager {
  public:
    const Player&       player;
    const EnemyManager& enemy_manager;

    UiManager(const Player& player, const EnemyManager& enemy_manager);

    void draw_player_xp_bar(void);
    void draw_player_hp_bar(void);
    void draw_enemy_hp_bar(void);
};
