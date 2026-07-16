#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "asset_manager.h"
#include "player.h"
#include <raylib.h>

typedef struct GameManager {
    AssetManager asset_manager;
    Player       player;
    Camera2D     camera;

} GameManager;

void game_manager_init(GameManager* gm);
void game_manager_update(GameManager* gm, const float dt, const Vector2 world_mouse);
void game_manager_draw(const GameManager* gm);
void game_manager_shutdown(GameManager* gm);

#endif // GAME_MANAGER_H
