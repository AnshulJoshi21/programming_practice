#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>

typedef struct {
    Vector2 center;
    float   radius;
    Color   color;
    float   speed;
    Vector2 direction;
    int     damage;
    float   max_lifetime;
    float   lifetime;
} Bullet;

void bullet_init(Bullet* bullet, const Vector2 start_pos, const Vector2 target_pos);
void bullet_update(Bullet* bullet, const float dt);
void bullet_draw(const Bullet* bullet);

#endif // BULLET_H
