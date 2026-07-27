#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "bullets/bullet_manager.h"
#include "collision_manager.h"
#include "drops/drop_manager.h"
#include "enemies/enemy_manager.h"
#include "player.h"
#include "ui_manager.h"
#include "upgrade_manager.h"
#include <raylib.h>

typedef enum GameState {
    GAME_STATE_TITLE,
    GAME_STATE_RUNNING,
    GAME_STATE_UPGRADE,
    GAME_STATE_EXIT,
} GameState;

typedef struct GameManager {
    GameState current_state;

    Player        player;
    EnemyManager  enemy_manager;
    BulletManager bullet_manager;
    DropManager   drop_manager;

    CollisionManager collision_manager;
    UiManager        ui_manager;
    UpgradeManager   upgrade_manager;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager* gm);
void game_manager_update(GameManager* gm, const float dt);
void game_manager_draw(GameManager* gm, const Vector2 world_mouse);

#endif // GAME_MANAGER_H
