#ifndef PLAYER_H
#define PLAYER_H

#include "sprite_data.h"
#include <raylib.h>

typedef enum PlayerState {

    P_STATE_IDLE = 0,
    P_STATE_RUN,
    P_STATE_ATTACK,
    P_STATE_DEATH,
    P_STATE_HURT,
    P_STATE_JUMP,
    P_STATE_UPTO_FALL,
    P_STATE_FALL,
    P_STATE_EDGE_GRAB,
    P_STATE_EDGE_IDLE,
    P_STATE_WALL_SLIDE,
    P_STATE_CROUCH,
    P_STATE_DASH,
    P_STATE_DASH_ATTACK,
    P_STATE_SLIDE,
    P_STATE_LADDER_GRAB,

    P_STATE_MAX

} PlayerState;

typedef struct Animation {
    SpriteType start_frame;
    SpriteType end_frame;
    float frame_speed;

} Animation;

typedef struct Player {
    PlayerState current_state;

    Rectangle source;
    Rectangle dest;
    Rectangle collider;
    Vector2 origin;

    float initial_h_speed;
    float h_speed;
    float dash_speed_max;
    float dash_speed;
    float v_speed;
    float direction_x;

    float jump_force;
    float gravity;

    float scale;
    float rotation;
    Color tint;

    float frame_timer;
    SpriteType frame_index;

    bool on_ground;
    bool is_attacking;

} Player;

void player_init(Player *p);
void player_draw(const Player *p, const Texture2D sheet);
void player_update(Player *p, const float dt);

#endif // PLAYER_H
