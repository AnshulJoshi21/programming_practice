#ifndef BULLET_PROJECTILE_H
#define BULLET_PROJECTILE_H

#include "bullet_data.h"
#include <raylib.h>

typedef enum ProjectileType {
    PROJECTILE_TYPE_MAGIC_MISSILE,
    PROJECTILE_TYPE_MAX,
} ProjectileType;

typedef struct ProjectileDef {
    const char*   name;
    BulletPattern pattern;
    DamageMode    damage_mode;
    float         radius;
    Color         color;
    float         speed;
    float         damage;
    float         fire_rate;
    float         lifetime;
} ProjectileDef;

extern const ProjectileDef projectile_db[PROJECTILE_TYPE_MAX];

typedef struct ProjectileConfig {
    Vector2 center;
    Vector2 target_pos;
    bool    homing;
} ProjectileConfig;

typedef struct ProjectileBullet {
    ProjectileType type;
    int            level;
    Vector2        center;
    Vector2        direction;
    float          lifetime;
    bool           homing;
    const Vector2* target_pos;
} ProjectileBullet;

void projectile_init(ProjectileBullet*       bullet,
                     const EntityConfig*     econfig,
                     const ProjectileConfig* config);
void projectile_update(ProjectileBullet* bullet, const float dt);
void projectile_draw(const ProjectileBullet* bullet);

#endif // BULLET_PROJECTILE_H
