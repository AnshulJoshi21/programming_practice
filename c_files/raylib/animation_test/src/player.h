#pragma once

#include "animation.h"
#include "input.h"
#include "texture_manager.h"

#include <raylib.h>

typedef enum {
    PLAYER_STATE_ATTACK,
    PLAYER_STATE_CAST,
    PLAYER_STATE_CLIMB,
    PLAYER_STATE_CROUCH,
    PLAYER_STATE_DIE,
    PLAYER_STATE_FALL,
    PLAYER_STATE_HURT,
    PLAYER_STATE_IDLE,
    PLAYER_STATE_JUMP,
    PLAYER_STATE_RUN,
    PLAYER_STATE_SLIDE,
    PLAYER_STATE_SOMERSAULT,
    PLAYER_STATE_WALK,

    PLAYER_STATE_MAX,

} PlayerState;

typedef struct {
    const AnimationConfig *animation_config;

    PlayerState state;
    PlayerState prev_state;
    bool        state_locked;

    Vector2   scale;
    Rectangle source;
    Rectangle dest;
    Vector2   origin;
    float     rotation;
    Color     tint;

    Vector2 direction;

    float speed_horizontal;
    float speed_vertical;
    float run_speed_multiplier;

    float jump_force;
    float gravity;

    bool can_jump;
    bool facing_left;

    InputMap  input_map[ACTION_MAX];
    Animation animation;

} Player;

void player_init(Player               *player,
                 const AnimationConfig animation_config[ANIMATION_TYPE_MAX]);
void player_update(Player *player, const float dt);
void player_draw(const Player *player);
