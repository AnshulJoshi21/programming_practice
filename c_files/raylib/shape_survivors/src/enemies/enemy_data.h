#ifndef ENEMY_DATA_H
#define ENEMY_DATA_H

#include <raylib.h>

typedef enum {
    ENEMY_TYPE_BAT,
    ENEMY_TYPE_ZOMBIE,
    ENEMY_TYPE_GHOST,
    ENEMY_TYPE_VAMPIRE,
    ENEMY_TYPE_DEMON,

    ENEMY_TYPE_MAX,
} EnemyType;

typedef struct {
    const char* name;
    Vector2     size;
    float       speed;
    int         hp;
    int         damage;
} EnemyData;

extern const EnemyData enemy_db[ENEMY_TYPE_MAX];

#endif // ENEMY_DATA_H
