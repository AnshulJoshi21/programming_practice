#pragma once

#include "bullets/bullet.hpp"
#include "components.hpp"
#include <raylib.h>

class Player {
  public:
    Components::Level     level;
    Components::Xp        xp;
    Components::Position  position;
    Components::Rect      rect;
    Components::Rotation  rotation;
    Components::Color_    color;
    Components::Text      text;
    Components::Movement  movement;
    Components::Health    health;
    Components::Animation animation;
    Components::Timer     bullet_timer;
    BulletConfig          bullet_config;

    Player();

    void handle_input(void);
    void update(const float dt);
    void draw(void) const;
};
