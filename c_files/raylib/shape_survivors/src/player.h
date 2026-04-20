#ifndef PLAYER_H
#define PLAYER_H

#include "components.h"

#include "bullets/bullet.h"

typedef struct Player {
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

} Player;

void player_init(Player *player);
void player_draw(const Player *player);
void player_update(Player *player, const float dt);

#endif  // PLAYER_H
