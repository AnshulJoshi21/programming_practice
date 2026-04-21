#pragma once

#include "bullets/bullet.hpp"
#include "components.hpp"

class Player {
  public:
    LevelComponent level;
    XpComponent xp;
    PositionComponent position;
    RectComponent rect;
    RotationComponent rotation;
    ColorComponent color;
    TextComponent text;
    MoveComponent move;
    HealthComponent health;
    AnimationComponent animation;
    TimerComponent bullet_timer;
    BulletConfig bullet_config;

    Player();

    void draw(void) const;
    void update(const float dt);
};
