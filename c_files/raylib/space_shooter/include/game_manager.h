#ifndef GAME_MANGER_H
#define GAME_MANGER_H

#include "entities/entity_background.h"
#include "entities/entity_player.h"

#include <raylib.h>

typedef struct GameManager
{
    Background background;
    Player player;

    Camera2D camera;

} GameManager;

void gm_init(GameManager *gm, const Texture2D spritesheet,
             const Texture2D background_texture);
void gm_draw(const GameManager *gm);
void gm_update(GameManager *gm, float dt, Vector2 mouse_pos_world);

#endif // GAME_MANGER_H
