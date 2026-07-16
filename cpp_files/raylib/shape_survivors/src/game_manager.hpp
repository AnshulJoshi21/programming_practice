#pragma once

#include "bullets/bullet_manager.hpp"
#include "collision_manager.hpp"
#include "drops/drop_manager.hpp"
#include "enemies/enemy_manager.hpp"
#include "player.hpp"
#include "ui_manager.hpp"
#include "upgrade_manager.hpp"
#include <raylib.h>

enum class GameState {
    TITLE,
    RUNNING,
    UPGRADE,
    EXIT,
};

class GameManager {
  public:
    GameState        state;
    Player           player;
    EnemyManager     enemy_manager;
    BulletManager    bullet_manager;
    DropManager      drop_manager;
    CollisionManager collision_manager;
    UiManager        ui_manager;
    UpgradeManager   upgrade_manager;
    Camera2D         camera;

    GameManager();

    void    update_camera(void);
    Vector2 get_player_target(void);
    void    update(const float dt);
    void    draw(const Vector2& world_mouse);
};
