#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "bullets/bullet_manager.h"
#include "enemies/enemy_manager.h"
#include "player.h"
#include <raylib.h>

typedef enum GameState {
    GAME_STATE_TITLE,
    GAME_STATE_RUNNING,
    GAME_STATE_UPGRADE,
    GAME_STATE_EXIT,
} GameState;

typedef struct GameManager {
    GameState     current_state;
    Player        player;
    EnemyManager  enemy_manager;
    BulletManager bullet_manager;

    Camera2D camera;
} GameManager;

void game_manager_init(GameManager* gm);
void game_manager_update(GameManager* gm, const float dt, const Vector2* world_mouse);
void game_manager_draw(const GameManager* gm);

#endif // GAME_MANAGER_H
