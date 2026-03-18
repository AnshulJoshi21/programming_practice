#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "ecs.h"

#include <raylib.h>

typedef struct GameManager
{
    World world;
    int player_id;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_draw(const GameManager *gm);
void game_manager_update(GameManager *gm, const float dt);

#endif // GAME_MANAGER_H
