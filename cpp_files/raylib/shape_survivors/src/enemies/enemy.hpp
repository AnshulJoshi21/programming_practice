#pragma once

#include "enemy_data.hpp"
#include <raylib.h>

static const float ENEMY_MAX_HIT_TIMER = 0.1f;

class Enemy {
  public:
    Rectangle rect;
    Vector2   origin;
    float     rotation;
    Color     color;
    float     speed;
    Vector2   direction;
    float     damage;
    float     hp;
    float     hit_timer;

    Enemy(const EnemyType type, const Vector2& target_pos);

    void update(const float dt, const Vector2& target_pos);
    void draw(void) const;
};
