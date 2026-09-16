#ifndef PLAYER_H
#define PLAYER_H

#include "timer.h"
#include <raylib.h>

typedef struct {
    int       level;
    int       xp;
    int       xp_next;
    Rectangle rect;
    Vector2   origin;
    float     rotation;
    Color     color;
    float     speed;
    Vector2   direction;
    int       max_hp;
    int       hp;
    float     max_hit_timer;
    float     hit_timer;

    IntervalTimer projectile_timer;
} Player;

int  player_get_xp_next(Player* player);
void player_init(Player* player);
void player_update(Player* player, const float dt);
void player_draw(const Player* player);

#endif // PLAYER_H
