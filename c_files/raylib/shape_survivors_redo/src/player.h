#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

static const float PLAYER_MAX_HP        = 100.0f;
static const float PLAYER_MAX_HIT_TIMER = 0.2f;
static const float PLAYER_SIZE          = 40.0f;
static const float PLAYER_SPEED         = 240.0f;

typedef struct Player {
    Rectangle rect;
    Vector2   origin;
    float     rotation;
    Color     color;
    float     speed;
    Vector2   direction;
    float     hp;
    float     hit_timer;
} Player;

void player_init(Player* player);
void player_update(Player* player, const float dt);
void player_draw(const Player* player);

#endif // PLAYER_H
