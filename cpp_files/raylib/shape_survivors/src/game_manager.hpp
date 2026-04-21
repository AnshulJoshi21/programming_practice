#pragma once

#include "bullets/bullet_manager.hpp"
#include "drops/drop_manager.hpp"
#include "enemies/enemy_manager.hpp"
#include "player.hpp"
#include <raylib.h>

class GameManager {
  private:
    void camera_update(void);
    Vector2 get_player_target(void);

  public:
    Player player;
    EnemyManager enemy_manager;
    BulletManager bullet_manager;
    DropManager drop_manager;

    Camera2D camera;

    GameManager();

    void draw(void) const;
    void update(const float dt);
};
