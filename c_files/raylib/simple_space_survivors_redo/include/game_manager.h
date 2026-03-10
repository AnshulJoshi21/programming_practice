#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "enemy_manager.h"
#include "player.h"
#include "starfield.h"

#include <raylib.h>

typedef struct GameManager
{
    Texture2D spritesheet;

    Starfield starfield;

    Player player;
    EnemyManager enemy_manager;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_draw(const GameManager *gm, const Texture2D spritesheet);
void game_manager_update(GameManager *gm, const float dt);

#endif // GAME_MANAGER_H
