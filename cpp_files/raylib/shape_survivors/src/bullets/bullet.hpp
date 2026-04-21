#pragma once

#include "../components.hpp"

struct BulletConfig {
    int damage;
    float speed;
    float lifetime;
};

class Bullet {
  public:
    PositionComponent position;
    CircleComponent circle;
    ColorComponent color;
    MoveComponent move;
    DamageComponent damage;
    LifetimeComponent lifetime;

    Bullet(const BulletConfig bullet_config, const Vector2 start_pos,
           const Vector2 target_pos);

    void draw(void) const;
    void update(const float dt);
};
