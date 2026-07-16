#pragma once

#include "../components.hpp"

class Enemy {
  public:
    Components::Position  position;
    Components::Rect      rect;
    Components::Rotation  rotation;
    Components::Color_    color;
    Components::Text      text;
    Components::Movement  movement;
    Components::Health    health;
    Components::Damage    damage;
    Components::Animation animation;

    Enemy(const Vector2& target_pos);

    void update(const float dt, const Vector2& target_pos);
    void draw(void) const;
};
