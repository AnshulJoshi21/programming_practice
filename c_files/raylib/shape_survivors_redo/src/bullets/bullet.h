#ifndef BULLET_H
#define BULLET_H

#include "bullet_data.h"
#include <raylib.h>

typedef struct BulletConfig {
    int        level;
    BulletType type;
    Vector2    center;

    union {
        struct {
            bool homing;

            bool piercing;
            int  pierce_count;

            bool bouncing;
            int  bounce_count;

            const Vector2* target;
        } projectile;

        struct {
            const Vector2* origin;
        } orbital;
    } data;
} BulletConfig;

typedef struct Bullet {
    BulletType type;
    Vector2    center;
    float      damage;
    float      lifetime;

    union {
        struct {
            const Vector2* target_pos;
            Vector2        direction;
        } projectile;

        struct {
            float          angle;
            const Vector2* origin;
        } orbital;
    } data;

} Bullet;

void bullet_init(Bullet* bullet, const BulletConfig* config);
void bullet_update(Bullet* bullet, const float dt);
void bullet_draw(const Bullet* bullet);

#endif // BULLET_H
