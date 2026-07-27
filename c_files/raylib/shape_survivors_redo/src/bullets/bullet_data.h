#ifndef BULLET_DATA_H
#define BULLET_DATA_H

#include <raylib.h>

typedef enum BulletPattern {
    BULLET_PATTERN_PROJECTILE,
    BULLET_PATTERN_ORBITAL,
    BULLET_PATTERN_MAX,
} BulletPattern;

typedef enum BulletType {
    BULLET_TYPE_MAGIC_MISSILES,
    BULLET_TYPE_ORBITING_ORBS,
    BULLET_TYPE_MAX,
} BulletType;

typedef struct BulletDef {
    BulletType    type;
    BulletPattern pattern;
    const char*   name;
    const char*   description;
    float         radius;
    Color         color;
    float         damage;
    float         lifetime;
    int           max_count;

    union {
        struct {
            float fire_rate;
            float speed;
        } projectile;

        struct {
            float orbital_radius;
            float orbital_speed;
        } orbital;
    } data;
} BulletDef;

extern const BulletDef bullet_db[BULLET_TYPE_MAX];

#endif // BULLET_DATA_H
