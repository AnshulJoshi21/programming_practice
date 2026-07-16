#ifndef ENEMY_H
#define ENEMY_H

#include "../components.h"
#include <raylib.h>

typedef struct Enemy {
    CPosition  position;
    CRect      rect;
    CRotation  rotation;
    CColor     color;
    CText      text;
    CMovement  movement;
    CHealth    health;
    CDamage    damage;
    CAnimation animation;
} Enemy;

void enemy_init(Enemy* enemy, const Vector2 target_pos);
void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos);
void enemy_draw(const Enemy* enemy);

#endif // ENEMY_H
