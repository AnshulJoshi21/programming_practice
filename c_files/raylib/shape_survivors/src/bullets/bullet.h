#ifndef BULLET_H
#define BULLET_H

#include "../components.h"
#include <raylib.h>

typedef struct BulletConfig {
    int   damage;
    float speed;
    float lifetime;
} BulletConfig;

typedef struct Bullet {
    CPosition position;
    CCircle   circle;
    CColor    color;
    CMovement movement;
    CDamage   damage;
    CLifetime lifetime;
} Bullet;

void bullet_init(Bullet*            bullet,
                 const BulletConfig config,
                 const Vector2      start_pos,
                 const Vector2      target_pos);
void bullet_update(Bullet* bullet, const float dt);
void bullet_draw(const Bullet* bullet);

#endif // BULLET_H
