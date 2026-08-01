#ifndef BULLET_DATA_H
#define BULLET_DATA_H

#include <stdbool.h>

typedef enum BulletPattern {
    BULLET_PATTERN_PROJECTILE,
    BULLET_PATTERN_ORBITAL,
    BULLET_PATTERN_AREA,
    BULLET_PATTERN_MAX,
} BulletPattern;

typedef enum DamageMode {
    DAMAGE_MODE_INSTANT_HIT,
    DAMAGE_MODE_TICK, // DOD DAMAGE
    DAMAGE_MODE_ON_EXPIRE,
    DAMAGE_MODE_MAX,
} DamageMode;

typedef struct EntityConfig {
    int  type;
    int  pattern;
    int  level;
    bool homing;
} EntityConfig;

#endif // BULLET_DATA_H
