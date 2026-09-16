#ifndef BULLET_H
#define BULLET_H

#include "../player.h"
#include "../settings.h"
#include "bullet_data.h"
#include <raylib.h>


typedef struct {
    Vector2        center;
    float          speed;
    Vector2        direction;
    const Vector2* target_pos;
} Projectile;

typedef struct {
    Vector2       centers[MAX_ORBITALS];
    const Player* player;
    int           orbital_count;
    float         orbital_angle;
    float         orbital_radius;
    float         orbital_speed;
} Orbital;

typedef struct {
    int behaviour;
    int type;

    float radius;
    int   damage;
    Color color;
    float lifetime;

    union {
        Projectile projectile;
        Orbital    orbital;
    } bullet;
} Bullet;

typedef struct {
    const int level;
    const int behaviour;
    const int type;

    union {
        struct {
            const Vector2  start_pos;
            const Vector2* target_pos;
        } projectile;

        struct {
            const Player* player;
        } orbital;
    } bullet;
} BulletInitConfig;

void bullet_init(Bullet* bullet, const BulletInitConfig config);
void bullet_update(Bullet* bullet, const float dt);
void bullet_draw(const Bullet* bullet);

#endif // BULLET_H
