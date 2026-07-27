#pragma once

#include <raylib.h>

enum class BulletBehaviour {
    PROJECTILE,
    ORBITAL,
    AREA,
    COUNT,
};

struct ProjectileDef {
    float radius;
    Color color;
    float speed;
    float damage;
    float lifetime;
};
