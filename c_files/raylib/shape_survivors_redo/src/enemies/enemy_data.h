#ifndef ENEMY_DATA_H
#define ENEMY_DATA_H

#include <raylib.h>

typedef enum EnemyType {
    ENEMY_TYPE_SLIME,
    ENEMY_TYPE_RUNNER,
    ENEMY_TYPE_TANK,
    ENEMY_TYPE_SHOOTER,
    ENEMY_TYPE_BRUTE,
    ENEMY_TYPE_BOSS,
    ENEMY_TYPE_MAX
} EnemyType;

typedef struct EnemyDef {
    const char* name;
    float       hp;
    float       damage;
    float       speed;
    Vector2     size;
    Color       color;
} EnemyDef;

extern const EnemyDef enemy_db[ENEMY_TYPE_MAX];

#endif // ENEMY_DATA_H
