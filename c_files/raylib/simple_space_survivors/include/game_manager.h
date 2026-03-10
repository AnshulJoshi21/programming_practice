#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "player.h"
#include "starfield.h"

#include <raylib.h>

typedef struct GameManager
{
    Starfield starfield;

    Player player;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm, const Texture2D spritesheet);
void game_manager_draw(const GameManager *gm, const Texture2D spritesheet);
void game_manager_update(GameManager *gm, const float dt);

#endif // GAME_MANAGER_H
