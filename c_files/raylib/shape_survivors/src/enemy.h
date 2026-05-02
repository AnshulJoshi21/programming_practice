#ifndef PLAYER_H
#define PLAYER_H

#include "components.h"

typedef struct Player {
  PositionComponent position;
  RectComponent rect;
  RotationComponent rotation;
  ColorComponent color;
  TextComponent text;
  MoveComponent move;
  HealthComponent health;
  AnimationComponent animation;
  TimerComponent bullet_timer;

} Player;

void player_init(Player *player);
void player_draw(const Player *player);
void player_update(Player *player, const float dt);

#endif // PLAYER_H
