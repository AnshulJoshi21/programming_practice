#include "enemy_data.h"

const EnemyDef enemy_db[ENEMY_TYPE_MAX] = {
    [ENEMY_TYPE_SLIME] = {
        .name = "Slime",
        .hp = 20.0f,
        .damage = 5.0f,
        .speed = 80.0f,
        .size = {20, 20},
        .color = DARKGREEN,
    },

    [ENEMY_TYPE_RUNNER] = {
        .name = "Runner",
        .hp = 15.0f,
        .damage = 8.0f,
        .speed = 180.0f,
        .size = {16, 16},
        .color = ORANGE,
    },

    [ENEMY_TYPE_TANK] = {
        .name = "Tank",
        .hp = 80.0f,
        .damage = 15.0f,
        .speed = 45.0f,
        .size = {32, 32},
        .color = DARKGRAY,
    },

    [ENEMY_TYPE_SHOOTER] = {
        .name = "Shooter",
        .hp = 30.0f,
        .damage = 12.0f,
        .speed = 70.0f,
        .size = {22, 22},
        .color = PURPLE,
    },

    [ENEMY_TYPE_BRUTE] = {
        .name = "Brute",
        .hp = 120.0f,
        .damage = 25.0f,
        .speed = 35.0f,
        .size = {40, 40},
        .color = MAROON,
    },

    [ENEMY_TYPE_BOSS] = {
        .name = "Boss",
        .hp = 500.0f,
        .damage = 40.0f,
        .speed = 55.0f,
        .size = {64, 64},
        .color = RED,
    },
};
