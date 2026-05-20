#pragma once

#include "texture_manager.h"

#include <raylib.h>

typedef enum {
    ANIMATION_TYPE_AIR_ATTACK1,
    ANIMATION_TYPE_AIR_ATTACK2,
    ANIMATION_TYPE_AIR_ATTACK3_END,
    ANIMATION_TYPE_AIR_ATTACK3_LOOP,
    ANIMATION_TYPE_AIR_ATTACK3_READY,
    ANIMATION_TYPE_ATTACK1,
    ANIMATION_TYPE_ATTACK2,
    ANIMATION_TYPE_ATTACK3,
    ANIMATION_TYPE_BOW,
    ANIMATION_TYPE_BOW_JUMP,
    ANIMATION_TYPE_CAST,
    ANIMATION_TYPE_CAST_LOOP,
    ANIMATION_TYPE_CORNER_CLIMB,
    ANIMATION_TYPE_CORNER_GRAB,
    ANIMATION_TYPE_CORNER_JUMP,
    ANIMATION_TYPE_CROUCH,
    ANIMATION_TYPE_CROUCH_WALK,
    ANIMATION_TYPE_DIE,
    ANIMATION_TYPE_DROP_KICK,
    ANIMATION_TYPE_FALL,
    ANIMATION_TYPE_GET_UP,
    ANIMATION_TYPE_HURT,
    ANIMATION_TYPE_IDLE,
    ANIMATION_TYPE_IDLE2,
    ANIMATION_TYPE_ITEMS,
    ANIMATION_TYPE_JUMP,
    ANIMATION_TYPE_KICK,
    ANIMATION_TYPE_KNOCK_DOWN,
    ANIMATION_TYPE_LADDER_CLIMB,
    ANIMATION_TYPE_PUNCH,
    ANIMATION_TYPE_RUN,
    ANIMATION_TYPE_RUN2,
    ANIMATION_TYPE_RUN_PUNCH,
    ANIMATION_TYPE_SLIDE,
    ANIMATION_TYPE_SOMERSAULT,
    ANIMATION_TYPE_STAND,
    ANIMATION_TYPE_SWORD_DRAW,
    ANIMATION_TYPE_SWORD_SHEATHE,
    ANIMATION_TYPE_WALK,
    ANIMATION_TYPE_WALL_RUN,
    ANIMATION_TYPE_WALL_SLIDE,

    ANIMATION_TYPE_MAX,

} AnimationType;

typedef struct {
    const Texture2D *frames[16];
    int              frame_count;
    float            frame_duration;
    bool             loops;

} AnimationConfig;

typedef struct {
    int   current_anim_type;
    int   current_frame;
    float frame_timer;
    bool  is_finished;

} Animation;

void animation_config_init(
        AnimationConfig       animation_configs[ANIMATION_TYPE_MAX],
        const TextureManager *tm);

void animation_set(Animation *animation, const int anim_type);
void animation_update(
        Animation            *animation,
        const AnimationConfig animation_configs[ANIMATION_TYPE_MAX],
        const float           dt);
