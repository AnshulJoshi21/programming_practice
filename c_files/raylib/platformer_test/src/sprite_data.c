#include "sprite_data.h"

const Rectangle sprite_db[SPRITE_MAX] = {
    [SPRITE_IDLE_1] = {.x = 0, .y = 0, .width = 69, .height = 44},
    [SPRITE_IDLE_2] = {.x = 69, .y = 0, .width = 69, .height = 44},
    [SPRITE_IDLE_3] = {.x = 138, .y = 0, .width = 69, .height = 44},
    [SPRITE_IDLE_4] = {.x = 207, .y = 0, .width = 69, .height = 44},
    [SPRITE_IDLE_5] = {.x = 276, .y = 0, .width = 69, .height = 44},
    [SPRITE_IDLE_6] = {.x = 345, .y = 0, .width = 69, .height = 44},

    [SPRITE_RUN_1] = {.x = 0, .y = 44, .width = 69, .height = 44},
    [SPRITE_RUN_2] = {.x = 69, .y = 44, .width = 69, .height = 44},
    [SPRITE_RUN_3] = {.x = 138, .y = 44, .width = 69, .height = 44},
    [SPRITE_RUN_4] = {.x = 207, .y = 44, .width = 69, .height = 44},
    [SPRITE_RUN_5] = {.x = 276, .y = 44, .width = 69, .height = 44},
    [SPRITE_RUN_6] = {.x = 345, .y = 44, .width = 69, .height = 44},
    [SPRITE_RUN_7] = {.x = 0, .y = 88, .width = 69, .height = 44},
    [SPRITE_RUN_8] = {.x = 69, .y = 88, .width = 69, .height = 44},

    [SPRITE_ATTACK_1] = {.x = 138, .y = 88, .width = 69, .height = 44},
    [SPRITE_ATTACK_2] = {.x = 207, .y = 88, .width = 69, .height = 44},
    [SPRITE_ATTACK_3] = {.x = 276, .y = 88, .width = 69, .height = 44},
    [SPRITE_ATTACK_4] = {.x = 345, .y = 88, .width = 69, .height = 44},
    [SPRITE_ATTACK_5] = {.x = 0, .y = 132, .width = 69, .height = 44},
    [SPRITE_ATTACK_6] = {.x = 69, .y = 132, .width = 69, .height = 44},
    [SPRITE_ATTACK_7] = {.x = 138, .y = 132, .width = 69, .height = 44},
    [SPRITE_ATTACK_8] = {.x = 207, .y = 132, .width = 69, .height = 44},
    [SPRITE_ATTACK_9] = {.x = 276, .y = 132, .width = 69, .height = 44},
    [SPRITE_ATTACK_10] = {.x = 345, .y = 132, .width = 69, .height = 44},
    [SPRITE_ATTACK_11] = {.x = 0, .y = 176, .width = 69, .height = 44},
    [SPRITE_ATTACK_12] = {.x = 69, .y = 176, .width = 69, .height = 44},

    [SPRITE_DEATH_1] = {.x = 138, .y = 176, .width = 69, .height = 44},
    [SPRITE_DEATH_2] = {.x = 207, .y = 176, .width = 69, .height = 44},
    [SPRITE_DEATH_3] = {.x = 276, .y = 176, .width = 69, .height = 44},
    [SPRITE_DEATH_4] = {.x = 345, .y = 176, .width = 69, .height = 44},
    [SPRITE_DEATH_5] = {.x = 0, .y = 220, .width = 69, .height = 44},
    [SPRITE_DEATH_6] = {.x = 69, .y = 220, .width = 69, .height = 44},
    [SPRITE_DEATH_7] = {.x = 138, .y = 220, .width = 69, .height = 44},
    [SPRITE_DEATH_8] = {.x = 207, .y = 220, .width = 69, .height = 44},
    [SPRITE_DEATH_9] = {.x = 276, .y = 220, .width = 69, .height = 44},
    [SPRITE_DEATH_10] = {.x = 345, .y = 220, .width = 69, .height = 44},
    [SPRITE_DEATH_11] = {.x = 0, .y = 264, .width = 69, .height = 44},

    [SPRITE_HURT_1] = {.x = 69, .y = 264, .width = 69, .height = 44},
    [SPRITE_HURT_2] = {.x = 138, .y = 264, .width = 69, .height = 44},
    [SPRITE_HURT_3] = {.x = 207, .y = 264, .width = 69, .height = 44},
    [SPRITE_HURT_4] = {.x = 276, .y = 264, .width = 69, .height = 44},

    [SPRITE_JUMP_1] = {.x = 345, .y = 264, .width = 69, .height = 44},
    [SPRITE_JUMP_2] = {.x = 0, .y = 308, .width = 69, .height = 44},
    [SPRITE_JUMP_3] = {.x = 69, .y = 308, .width = 69, .height = 44},

    [SPRITE_UPTO_FALL_1] = {.x = 138, .y = 308, .width = 69, .height = 44},
    [SPRITE_UPTO_FALL_2] = {.x = 207, .y = 308, .width = 69, .height = 44},

    [SPRITE_FALL_1] = {.x = 276, .y = 308, .width = 69, .height = 44},
    [SPRITE_FALL_2] = {.x = 345, .y = 308, .width = 69, .height = 44},
    [SPRITE_FALL_3] = {.x = 0, .y = 352, .width = 69, .height = 44},

    [SPRITE_EDGE_GRAB_1] = {.x = 69, .y = 352, .width = 69, .height = 44},
    [SPRITE_EDGE_GRAB_2] = {.x = 138, .y = 352, .width = 69, .height = 44},
    [SPRITE_EDGE_GRAB_3] = {.x = 207, .y = 352, .width = 69, .height = 44},
    [SPRITE_EDGE_GRAB_4] = {.x = 276, .y = 352, .width = 69, .height = 44},
    [SPRITE_EDGE_GRAB_5] = {.x = 345, .y = 352, .width = 69, .height = 44},

    [SPRITE_EDGE_IDLE_1] = {.x = 0, .y = 396, .width = 69, .height = 44},
    [SPRITE_EDGE_IDLE_2] = {.x = 69, .y = 396, .width = 69, .height = 44},
    [SPRITE_EDGE_IDLE_3] = {.x = 138, .y = 396, .width = 69, .height = 44},
    [SPRITE_EDGE_IDLE_4] = {.x = 207, .y = 396, .width = 69, .height = 44},
    [SPRITE_EDGE_IDLE_5] = {.x = 276, .y = 396, .width = 69, .height = 44},
    [SPRITE_EDGE_IDLE_6] = {.x = 345, .y = 396, .width = 69, .height = 44},

    [SPRITE_WALL_SLIDE_1] = {.x = 0, .y = 440, .width = 69, .height = 44},
    [SPRITE_WALL_SLIDE_2] = {.x = 69, .y = 440, .width = 69, .height = 44},
    [SPRITE_WALL_SLIDE_3] = {.x = 138, .y = 440, .width = 69, .height = 44},

    [SPRITE_CROUCH_1] = {.x = 207, .y = 440, .width = 69, .height = 44},
    [SPRITE_CROUCH_2] = {.x = 276, .y = 440, .width = 69, .height = 44},
    [SPRITE_CROUCH_3] = {.x = 345, .y = 440, .width = 69, .height = 44},
    [SPRITE_CROUCH_4] = {.x = 0, .y = 484, .width = 69, .height = 44},
    [SPRITE_CROUCH_5] = {.x = 69, .y = 484, .width = 69, .height = 44},
    [SPRITE_CROUCH_6] = {.x = 138, .y = 484, .width = 69, .height = 44},

    [SPRITE_DASH_1] = {.x = 207, .y = 484, .width = 69, .height = 44},
    [SPRITE_DASH_2] = {.x = 276, .y = 484, .width = 69, .height = 44},
    [SPRITE_DASH_3] = {.x = 345, .y = 484, .width = 69, .height = 44},
    [SPRITE_DASH_4] = {.x = 0, .y = 528, .width = 69, .height = 44},
    [SPRITE_DASH_5] = {.x = 69, .y = 528, .width = 69, .height = 44},
    [SPRITE_DASH_6] = {.x = 138, .y = 528, .width = 69, .height = 44},
    [SPRITE_DASH_7] = {.x = 207, .y = 528, .width = 69, .height = 44},

    [SPRITE_DASH_ATTACK_1] = {.x = 276, .y = 528, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_2] = {.x = 345, .y = 528, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_3] = {.x = 0, .y = 572, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_4] = {.x = 69, .y = 572, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_5] = {.x = 138, .y = 572, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_6] = {.x = 207, .y = 572, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_7] = {.x = 276, .y = 572, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_8] = {.x = 345, .y = 572, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_9] = {.x = 0, .y = 616, .width = 69, .height = 44},
    [SPRITE_DASH_ATTACK_10] = {.x = 69, .y = 616, .width = 69, .height = 44},

    [SPRITE_SLIDE_1] = {.x = 138, .y = 616, .width = 69, .height = 44},
    [SPRITE_SLIDE_2] = {.x = 207, .y = 616, .width = 69, .height = 44},
    [SPRITE_SLIDE_3] = {.x = 276, .y = 616, .width = 69, .height = 44},
    [SPRITE_SLIDE_4] = {.x = 345, .y = 616, .width = 69, .height = 44},
    [SPRITE_SLIDE_5] = {.x = 0, .y = 660, .width = 69, .height = 44},

    [SPRITE_LADDER_GRAB_1] = {.x = 69, .y = 660, .width = 69, .height = 44},
    [SPRITE_LADDER_GRAB_2] = {.x = 138, .y = 660, .width = 69, .height = 44},
    [SPRITE_LADDER_GRAB_3] = {.x = 207, .y = 660, .width = 69, .height = 44},
    [SPRITE_LADDER_GRAB_4] = {.x = 276, .y = 660, .width = 69, .height = 44},
    [SPRITE_LADDER_GRAB_5] = {.x = 345, .y = 660, .width = 69, .height = 44},
    [SPRITE_LADDER_GRAB_6] = {.x = 0, .y = 704, .width = 69, .height = 44},
    [SPRITE_LADDER_GRAB_7] = {.x = 69, .y = 704, .width = 69, .height = 44},
    [SPRITE_LADDER_GRAB_8] = {.x = 138, .y = 704, .width = 69, .height = 44},
};

// ANIMATION FRAMES
const SpriteType idle_frames[] = {SPRITE_IDLE_1, SPRITE_IDLE_2, SPRITE_IDLE_3,
                                  SPRITE_IDLE_4, SPRITE_IDLE_5, SPRITE_IDLE_6};
const SpriteType run_frames[] = {SPRITE_RUN_1, SPRITE_RUN_2, SPRITE_RUN_3,
                                 SPRITE_RUN_4, SPRITE_RUN_5, SPRITE_RUN_6,
                                 SPRITE_RUN_7, SPRITE_RUN_8};
const SpriteType attack_frames[] = {
    SPRITE_ATTACK_1, SPRITE_ATTACK_2,  SPRITE_ATTACK_3,  SPRITE_ATTACK_4,
    SPRITE_ATTACK_5, SPRITE_ATTACK_6,  SPRITE_ATTACK_7,  SPRITE_ATTACK_8,
    SPRITE_ATTACK_9, SPRITE_ATTACK_10, SPRITE_ATTACK_11, SPRITE_ATTACK_12,
};
const SpriteType death_frames[] = {SPRITE_DEATH_1, SPRITE_DEATH_2,
                                   SPRITE_DEATH_3, SPRITE_DEATH_4,
                                   SPRITE_DEATH_5, SPRITE_DEATH_6,
                                   SPRITE_DEATH_7, SPRITE_DEATH_8,
                                   SPRITE_DEATH_9, SPRITE_DEATH_10,
                                   SPRITE_DEATH_11};
const SpriteType hurt_frames[] = {SPRITE_HURT_1, SPRITE_HURT_2, SPRITE_HURT_3,
                                  SPRITE_HURT_4};
const SpriteType jump_frames[] = {SPRITE_JUMP_1, SPRITE_JUMP_2, SPRITE_JUMP_3};
const SpriteType upto_fall_frames[] = {SPRITE_UPTO_FALL_1, SPRITE_UPTO_FALL_2};
const SpriteType fall_frames[] = {SPRITE_FALL_1, SPRITE_FALL_2, SPRITE_FALL_3};
const SpriteType edge_grab_frames[] = {SPRITE_EDGE_GRAB_1, SPRITE_EDGE_GRAB_2,
                                       SPRITE_EDGE_GRAB_3, SPRITE_EDGE_GRAB_4,
                                       SPRITE_EDGE_GRAB_5};
const SpriteType edge_idle_frames[] = {SPRITE_EDGE_IDLE_1, SPRITE_EDGE_IDLE_2,
                                       SPRITE_EDGE_IDLE_3, SPRITE_EDGE_IDLE_4,
                                       SPRITE_EDGE_IDLE_5, SPRITE_EDGE_IDLE_6};
const SpriteType wall_slide_frames[] = {SPRITE_WALL_SLIDE_1,
                                        SPRITE_WALL_SLIDE_2,
                                        SPRITE_WALL_SLIDE_3};
const SpriteType crouch_frames[] = {SPRITE_CROUCH_1, SPRITE_CROUCH_2,
                                    SPRITE_CROUCH_3, SPRITE_CROUCH_4,
                                    SPRITE_CROUCH_5, SPRITE_CROUCH_6};
const SpriteType dash_frames[] = {SPRITE_DASH_1, SPRITE_DASH_2, SPRITE_DASH_3,
                                  SPRITE_DASH_4, SPRITE_DASH_5, SPRITE_DASH_6,
                                  SPRITE_DASH_7};
const SpriteType dash_attack_frames[] = {
    SPRITE_DASH_ATTACK_1, SPRITE_DASH_ATTACK_2, SPRITE_DASH_ATTACK_3,
    SPRITE_DASH_ATTACK_4, SPRITE_DASH_ATTACK_5, SPRITE_DASH_ATTACK_6,
    SPRITE_DASH_ATTACK_7, SPRITE_DASH_ATTACK_8, SPRITE_DASH_ATTACK_9,
    SPRITE_DASH_ATTACK_10};
const SpriteType slide_frames[] = {SPRITE_SLIDE_1, SPRITE_SLIDE_2,
                                   SPRITE_SLIDE_3, SPRITE_SLIDE_4,
                                   SPRITE_SLIDE_5};
const SpriteType ladder_grab_frames[] = {
    SPRITE_LADDER_GRAB_1, SPRITE_LADDER_GRAB_2, SPRITE_LADDER_GRAB_3,
    SPRITE_LADDER_GRAB_4, SPRITE_LADDER_GRAB_5, SPRITE_LADDER_GRAB_6,
    SPRITE_LADDER_GRAB_7, SPRITE_LADDER_GRAB_8};
