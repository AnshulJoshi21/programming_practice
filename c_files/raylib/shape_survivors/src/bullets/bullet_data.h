#ifndef BULLET_DATA_H
#define BULLET_DATA_H

#include <raylib.h>

typedef struct SkillStats {
    int  level;
    bool magic_missile;
    bool orbiting_orbs;
    bool aura;
} SkillStats;

typedef enum BulletType {
    BULLET_PROJECTILE,
    BULLET_ORBITER,

    BULLET_MAX,
} BulletType;

typedef enum SkillType {
    SKILL_MAGIC_MISSILE,
    SKILL_ORBITING_ORBS,

    SKILL_MAX,
} SkillType;

typedef struct SkillDef {
    SkillType   skill_type;
    BulletType  bullet_type;
    const char* name;
    float       radius;
    Color       color;
    union {
        struct {
            float speed;
            int   damage;
            float lifetime;
        } projectile;

        struct {
            int   damage;
            float angular_radius;
        } orbiter;
    };
} SkillDef;

extern const SkillDef skill_db[SKILL_MAX];

#endif // BULLET_DATA_H
