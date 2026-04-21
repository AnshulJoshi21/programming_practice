#pragma once

#include "../components.hpp"

class Enemy {
  public:
    PositionComponent position;
    RectComponent rect;
    RotationComponent rotation;
    ColorComponent color;
    TextComponent text;
    MoveComponent move;
    HealthComponent health;
    DamageComponent damage;
    AnimationComponent animation;

    Enemy(const Vector2 target_pos);

    void draw(void) const;
    void update(const float dt, const Vector2 target_pos);
};
