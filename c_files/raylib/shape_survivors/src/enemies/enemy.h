#pragma once

#include "../components.h"

typedef struct {
    LevelComponent     level;
    PositionComponent  position;
    RectComponent      rect;
    RotationComponent  rotation;
    ColorComponent     color;
    TextComponent      text;
    MoveComponent      move;
    AnimationComponent animation;

} Enemy;

void enemy_init(Enemy* enemy, const int current_wave, const Vector2 target_pos);
void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos);
void enemy_draw(const Enemy* enemy);
