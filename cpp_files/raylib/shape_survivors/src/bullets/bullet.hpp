#pragma once

#include "../components.hpp"
#include <raylib.h>

struct BulletConfig {
    int   damage;
    float speed;
    float lifetime;
};

class Bullet {
  public:
    Components::Position position;
    Components::Circle   circle;
    Components::Color_   color;
    Components::Movement movement;
    Components::Damage   damage;
    Components::Lifetime lifetime;

    Bullet(const BulletConfig& config, const Vector2& start_pos, const Vector2& target_pos);

    void update(const float dt);
    void draw(void) const;
};
