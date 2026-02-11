#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <raylib.h>

typedef struct GameManager
{
    Camera2D camera;

} GameManager;

void gm_init(GameManager *gm, const Texture2D spritesheet,
             const Texture2D background_texture);
void gm_draw(const GameManager *gm);
void gm_update(GameManager *gm, float dt, Vector2 mouse_pos_world);

#endif // GAME_MANAGER_H
