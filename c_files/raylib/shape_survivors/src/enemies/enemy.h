#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

typedef struct {
    Rectangle rect;
    Vector2   origin;
    float     rotation;
    Color     color;
    float     speed;
    Vector2   direction;
    int       max_hp;
    int       hp;
    int       damage;
} Enemy;

void enemy_init(Enemy* enemy, const Vector2 target_pos);
void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos);
void enemy_draw(const Enemy* enemy);

#endif // ENEMY_H
