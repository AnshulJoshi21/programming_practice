#pragma once

#include "bullets/bullet_manager.hpp"
#include "drops/drop_manager.hpp"
#include "enemies/enemy_manager.hpp"
#include "player.hpp"

enum class CollisionType {
    CHECK,
    ONE_WAY,
    TWO_WAY,
};

class CollisionManager {
  public:
    Player&        player;
    EnemyManager&  enemy_manager;
    BulletManager& bullet_manager;
    DropManager&   drop_manager;

    CollisionManager(Player&        player,
                     EnemyManager&  enemy_manager,
                     BulletManager& bullet_manager,
                     DropManager&   drop_manager);

    void player_vs_enemy(void);
    void player_vs_drop(void);
    void bullet_vs_enemy(void);
    void enemy_vs_enemy(void);

    void update(void);
};
