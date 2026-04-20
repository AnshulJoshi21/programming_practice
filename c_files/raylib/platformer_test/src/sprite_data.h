#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include <raylib.h>

typedef enum SpriteType {
    SPRITE_IDLE_1,
    SPRITE_IDLE_2,
    SPRITE_IDLE_3,
    SPRITE_IDLE_4,
    SPRITE_IDLE_5,
    SPRITE_IDLE_6,

    SPRITE_RUN_1,
    SPRITE_RUN_2,
    SPRITE_RUN_3,
    SPRITE_RUN_4,
    SPRITE_RUN_5,
    SPRITE_RUN_6,
    SPRITE_RUN_7,
    SPRITE_RUN_8,

    SPRITE_ATTACK_1,
    SPRITE_ATTACK_2,
    SPRITE_ATTACK_3,
    SPRITE_ATTACK_4,
    SPRITE_ATTACK_5,
    SPRITE_ATTACK_6,
    SPRITE_ATTACK_7,
    SPRITE_ATTACK_8,
    SPRITE_ATTACK_9,
    SPRITE_ATTACK_10,
    SPRITE_ATTACK_11,
    SPRITE_ATTACK_12,

    SPRITE_DEATH_1,
    SPRITE_DEATH_2,
    SPRITE_DEATH_3,
    SPRITE_DEATH_4,
    SPRITE_DEATH_5,
    SPRITE_DEATH_6,
    SPRITE_DEATH_7,
    SPRITE_DEATH_8,
    SPRITE_DEATH_9,
    SPRITE_DEATH_10,
    SPRITE_DEATH_11,

    SPRITE_HURT_1,
    SPRITE_HURT_2,
    SPRITE_HURT_3,
    SPRITE_HURT_4,

    SPRITE_JUMP_1,
    SPRITE_JUMP_2,
    SPRITE_JUMP_3,

    SPRITE_UPTO_FALL_1,
    SPRITE_UPTO_FALL_2,

    SPRITE_FALL_1,
    SPRITE_FALL_2,
    SPRITE_FALL_3,

    SPRITE_EDGE_GRAB_1,
    SPRITE_EDGE_GRAB_2,
    SPRITE_EDGE_GRAB_3,
    SPRITE_EDGE_GRAB_4,
    SPRITE_EDGE_GRAB_5,

    SPRITE_EDGE_IDLE_1,
    SPRITE_EDGE_IDLE_2,
    SPRITE_EDGE_IDLE_3,
    SPRITE_EDGE_IDLE_4,
    SPRITE_EDGE_IDLE_5,
    SPRITE_EDGE_IDLE_6,

    SPRITE_WALL_SLIDE_1,
    SPRITE_WALL_SLIDE_2,
    SPRITE_WALL_SLIDE_3,

    SPRITE_CROUCH_1,
    SPRITE_CROUCH_2,
    SPRITE_CROUCH_3,
    SPRITE_CROUCH_4,
    SPRITE_CROUCH_5,
    SPRITE_CROUCH_6,

    SPRITE_DASH_1,
    SPRITE_DASH_2,
    SPRITE_DASH_3,
    SPRITE_DASH_4,
    SPRITE_DASH_5,
    SPRITE_DASH_6,
    SPRITE_DASH_7,

    SPRITE_DASH_ATTACK_1,
    SPRITE_DASH_ATTACK_2,
    SPRITE_DASH_ATTACK_3,
    SPRITE_DASH_ATTACK_4,
    SPRITE_DASH_ATTACK_5,
    SPRITE_DASH_ATTACK_6,
    SPRITE_DASH_ATTACK_7,
    SPRITE_DASH_ATTACK_8,
    SPRITE_DASH_ATTACK_9,
    SPRITE_DASH_ATTACK_10,

    SPRITE_SLIDE_1,
    SPRITE_SLIDE_2,
    SPRITE_SLIDE_3,
    SPRITE_SLIDE_4,
    SPRITE_SLIDE_5,

    SPRITE_LADDER_GRAB_1,
    SPRITE_LADDER_GRAB_2,
    SPRITE_LADDER_GRAB_3,
    SPRITE_LADDER_GRAB_4,
    SPRITE_LADDER_GRAB_5,
    SPRITE_LADDER_GRAB_6,
    SPRITE_LADDER_GRAB_7,
    SPRITE_LADDER_GRAB_8,

    SPRITE_MAX

} SpriteType;

extern const Rectangle sprite_db[SPRITE_MAX];

extern const SpriteType idle_frames[];
extern const SpriteType run_frames[];
extern const SpriteType attack_frames[];
extern const SpriteType death_frames[];
extern const SpriteType hurt_frames[];
extern const SpriteType jump_frames[];
extern const SpriteType upto_fall_frames[];
extern const SpriteType fall_frames[];
extern const SpriteType edge_grab_frames[];
extern const SpriteType edge_idle_frames[];
extern const SpriteType wall_slide_frames[];
extern const SpriteType crouch_frames[];
extern const SpriteType dash_frames[];
extern const SpriteType dash_attack_frames[];
extern const SpriteType slide_frames[];
extern const SpriteType ladder_grab_frames[];

#endif // SPRITE_DATA_H
