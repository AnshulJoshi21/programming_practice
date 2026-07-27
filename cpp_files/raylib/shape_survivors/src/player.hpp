#pragma once

#include <raylib.h>

static const float PLAYER_SPEED         = 240.0f;
static const float PLAYER_MAX_HP        = 100.0f;
static const float PLAYER_MAX_HIT_TIMER = 0.2f;
static const float PLAYER_SIZE          = 40.0f;

class Player {
  public:
    Rectangle rect;
    Vector2   origin;
    float     rotation;
    Color     color;
    float     speed;
    Vector2   direction;
    float     hp;
    float     hit_timer;

    Player();

    void handle_input(void);
    void update(const float dt);
    void draw(void) const;
};
