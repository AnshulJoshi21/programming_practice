#pragma once

#include "./bullets/bullet_manager.h"
#include "components.h"

typedef struct {
    LevelComponent     level;
    XpComponent        xp;
    PositionComponent  position;
    RectComponent      rect;
    RotationComponent  rotation;
    ColorComponent     color;
    TextComponent      text;
    MoveComponent      move;
    HealthComponent    health;
    AnimationComponent animation;
    BulletConfig       bullet_config;
    TimerComponent     bullet_timer;

} Player;

void player_init(Player* player);
void player_update(Player* player, const float dt);
void player_draw(const Player* player);
