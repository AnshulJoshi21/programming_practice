#ifndef ENEMY_H
#define ENEMY_H

#include "enemy_data.h"
#include <raylib.h>

typedef struct Enemy {
    EnemyType type;
    Vector2   pos;
    Vector2   direction;
    float     hp;
    float     hit_timer;
} Enemy;

void enemy_init(Enemy* enemy, const EnemyType type, const Vector2 target_pos);
void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos);
void enemy_draw(const Enemy* enemy);

#endif // ENEMY_H
