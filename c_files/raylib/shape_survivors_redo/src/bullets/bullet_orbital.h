#ifndef BULLET_ORBITAL_h
#define BULLET_ORBITAL_h

#include "bullet_data.h"
#include <raylib.h>

typedef enum OrbitalType {
    ORBITAL_TYPE_ORBITING_ORBS,
    ORBITAL_TYPE_MAX,
} OrbitalType;

typedef struct OrbitalDef {
    const char*   name;
    BulletPattern pattern;
    DamageMode    damage_mode;
    float         radius;
    Color         color;
    float         damage;
    float         orbital_radius;
    float         orbital_speed;
    float         lifetime;
} OrbitalDef;

extern const OrbitalDef orbital_db[ORBITAL_TYPE_MAX];

typedef struct OrbitalConfig {
    const Vector2* origin;
    float          angle;
} OrbitalConfig;

typedef struct OrbitalBullet {
    OrbitalType    type;
    int            level;
    Vector2        center;
    float          angle;
    const Vector2* origin;
    float          lifetime;
} OrbitalBullet;

void orbital_init(OrbitalBullet* bullet, const EntityConfig* econfig, const OrbitalConfig* config);
void orbital_update(OrbitalBullet* bullet, const float dt);

#endif // BULLET_ORBITAL_h
