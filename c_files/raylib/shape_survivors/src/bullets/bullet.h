#ifndef BULLET_H
#define BULLET_H

#include "../components.h"

typedef enum BulletType {
    BULLET_SINGLE,
    BULLET_SPREAD,  // IN A CONE SHAPE
    BULLET_HEAVY,
    BULLET_RAPID,
    BULLET_REVOLVING,
    BULLET_MAX

} BulletType;

typedef struct Bullet {
    BulletType type;
    PositionComponent position;
    CircleComponent circle;
    ColorComponent color;
    MoveComponent move;
    DamageComponent damage;
    LifetimeComponent lifetime;

} Bullet;

typedef struct BulletConfig {
    float damage;
    float speed;
    float lifetime;

} BulletConfig;

void bullet_init(Bullet *bullet, const BulletType type, const Vector2 start_pos,
                 const Vector2 target_pos, const BulletConfig config);
void bullet_draw(const Bullet *bullet);
void bullet_update(Bullet *bullet, const float dt);

#endif  // BULLET_H
