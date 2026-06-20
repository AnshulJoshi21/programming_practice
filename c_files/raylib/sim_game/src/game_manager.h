#pragma once

#include "components.h"
#include <raylib.h>

typedef struct {
    Camera2D camera;

} GameManager;

void game_manager_init(GameManager* gm);
void game_manager_update(GameManager* gm, const float dt);
void game_manager_draw(const GameManager* gm);
