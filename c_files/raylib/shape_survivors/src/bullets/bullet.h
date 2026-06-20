#pragma once

#include "../components.h"

typedef struct {
    int   damage;
    float speed;
    float lifetime;
} BulletConfig;

typedef struct {
    PositionComponent position;
    CircleComponent   circle;
    ColorComponent    color;
    MoveComponent     move;
    DamageComponent   damage;
    LifetimeComponent lifetime;

} Bullet;

void bullet_init(Bullet*             bullet,
                 const BulletConfig* config,
                 const Vector2       start_pos,
                 const Vector2       target_pos);
void bullet_update(Bullet* bullet, const float dt);
void bullet_draw(const Bullet* bullet);
