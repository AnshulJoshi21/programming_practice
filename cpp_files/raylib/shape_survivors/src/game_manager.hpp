#pragma once

#include "enemies/enemy_manager.hpp"
#include "player.hpp"
#include <raylib.h>

enum class GameState {
    TITLE,
    RUNNING,
    UPGRADE,
    EXIT,
};

class GameManager {
  public:
    GameState    current_state;
    Player       player;
    EnemyManager enemy_manager;
    Camera2D     camera;

    GameManager();

    void update_camera(void);
    void update(const float dt);
    void draw(const Vector2& world_mouse) const;
};
