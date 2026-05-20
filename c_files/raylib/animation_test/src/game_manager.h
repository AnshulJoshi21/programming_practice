#pragma once

#include "player.h"
#include "texture_manager.h"

#include <raylib.h>

typedef struct {
    TextureManager  texture_manager;
    AnimationConfig animation_configs[ANIMATION_TYPE_MAX];

    Player player;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_update(GameManager *gm, const float dt);
void game_manager_draw(const GameManager *gm);
void game_manager_shutdown(GameManager *gm);
