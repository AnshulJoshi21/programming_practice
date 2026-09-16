#ifndef BULLET_DATA_H
#define BULLET_DATA_H

#include <raylib.h>

typedef enum {
    BULLET_BEHAVIOUR_PROJECTILE,
    BULLET_BEHAVIOUR_ORBITAL,
    BULLET_BEHAVIOUR_MAX,
} BulletBehaviour;

typedef enum {
    BULLET_TYPE_MAGIC_MISSILE,
    BULLET_TYPE_ORBITAL_ORBS,
    BULLET_TYPE_MAX,
} BulletType;

typedef struct {
    float base_speed;
} ProjectileData;

typedef struct {
    int   base_orbital_count;
    float base_orbital_radius;
    float base_orbital_speed;
} OrbitalData;

typedef struct {
    int         behaviour;
    int         type;
    const char* name;

    float base_radius;
    int   base_damage;
    float base_lifetime;

    union {
        ProjectileData projectile;
        OrbitalData    orbital;
    } bullet;
} BulletData;

extern const BulletData bullet_db[BULLET_BEHAVIOUR_MAX][BULLET_TYPE_MAX];

#endif // BULLET_DATA_H
