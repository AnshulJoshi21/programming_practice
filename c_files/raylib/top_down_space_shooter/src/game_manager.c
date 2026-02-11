#include "../include/game_manager.h"

#include <assert.h>

void gm_init(GameManager *gm, const Texture2D spritesheet,
             const Texture2D background_texture)
{
    assert(gm);
}

void gm_draw(const GameManager *gm) { assert(gm); }

void gm_update(GameManager *gm, float dt, Vector2 mouse_pos_world)
{
    assert(gm);
}
