#ifndef BULLET_H
#define BULLET_H

#include "../components.h"
#include "bullet_data.h"
#include <raylib.h>

typedef struct Bullet {
    SkillType skil_type;
    CLevel    level;
    CPosition position;
    CCircle   circle;
    CColor    color;
    union {
        struct {
            CMovement movement;
            CDamage   damage;
            CLifetime lifetime;
            bool      homing;
            bool      piercing;
            bool      bouncing;
            int       pierce_count;
            int       bounce_count;
        } projectile;

        struct {
            CDamage   damage;
            float     angular_radius;
            CLifetime lifetime;
        } orbiter;
    } data;
} Bullet;

void bullet_init(Bullet*         bullet,
                 const SkillType skill_type,
                 const Vector2   start_pos,
                 const Vector2   target_pos);
void bullet_update(Bullet* bullet, const float dt);
void bullet_draw(const Bullet* bullet);

#endif // BULLET_H
