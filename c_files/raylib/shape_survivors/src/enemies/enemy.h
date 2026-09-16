#ifndef ENEMY_H
#define ENEMY_H

#include "../player.h"
#include "enemy_data.h"
#include <raylib.h>

typedef struct {
    const Player* player;
    Rectangle     rect;
    Vector2       origin;
    float         rotation;
    Color         color;
    float         speed;
    Vector2       direction;
    int           damage;
    int           max_hp;
    int           hp;
    float         max_hit_timer;
    float         hit_timer;
} Enemy;

void enemy_init(Enemy* enemy, const EnemyType type, const Player* player);
void enemy_update(Enemy* enemy, const float dt);
void enemy_draw(const Enemy* enemy);

#endif // ENEMY_H
