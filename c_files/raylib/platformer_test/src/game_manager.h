#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "player.h"
#include <raylib.h>

typedef struct GameManager {
    Player player;
    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_draw(const GameManager *gm, const Texture2D sheet);
void game_manager_update(GameManager *gm, const float dt);

#endif // GAME_MANAGER_H
