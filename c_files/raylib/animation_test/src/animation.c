#include "animation.h"

#include <assert.h>

void animation_config_init(
        AnimationConfig       animation_configs[ANIMATION_TYPE_MAX],
        const TextureManager *tm)
{
    assert(tm);

    animation_configs[ANIMATION_TYPE_AIR_ATTACK1]
            = (AnimationConfig){{
                                        &tm->air_attack1_00,
                                        &tm->air_attack1_01,
                                        &tm->air_attack1_02,
                                        &tm->air_attack1_03,
                                },
                                4,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_AIR_ATTACK2]
            = (AnimationConfig){{
                                        &tm->air_attack2_00,
                                        &tm->air_attack2_01,
                                        &tm->air_attack2_02,
                                },
                                3,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_AIR_ATTACK3_END]
            = (AnimationConfig){{
                                        &tm->air_attack_3_end_00,
                                        &tm->air_attack_3_end_01,
                                        &tm->air_attack_3_end_02,

                                },
                                3,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_AIR_ATTACK3_LOOP]
            = (AnimationConfig){{
                                        &tm->air_attack3_loop_00,
                                        &tm->air_attack3_loop_01,
                                },
                                2,
                                0.10f,
                                true};

    animation_configs[ANIMATION_TYPE_AIR_ATTACK3_READY]
            = (AnimationConfig){{
                                        &tm->air_attack3_ready_00,
                                },
                                1,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_ATTACK1]
            = (AnimationConfig){{
                                        &tm->attack1_00,
                                        &tm->attack1_01,
                                        &tm->attack1_02,
                                        &tm->attack1_03,
                                        &tm->attack1_04,
                                },
                                5,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_ATTACK2]
            = (AnimationConfig){{
                                        &tm->attack2_00,
                                        &tm->attack2_01,
                                        &tm->attack2_02,
                                        &tm->attack2_03,
                                        &tm->attack2_04,
                                        &tm->attack2_05,
                                },
                                6,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_ATTACK3]
            = (AnimationConfig){{
                                        &tm->attack3_00,
                                        &tm->attack3_01,
                                        &tm->attack3_02,
                                        &tm->attack3_03,
                                        &tm->attack3_04,
                                        &tm->attack3_05,
                                },
                                6,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_BOW]
            = (AnimationConfig){{
                                        &tm->bow_00,
                                        &tm->bow_01,
                                        &tm->bow_02,
                                        &tm->bow_03,
                                        &tm->bow_04,
                                        &tm->bow_05,
                                        &tm->bow_06,
                                        &tm->bow_07,
                                        &tm->bow_08,
                                },
                                9,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_BOW_JUMP]
            = (AnimationConfig){{
                                        &tm->bow_jump_00,
                                        &tm->bow_jump_01,
                                        &tm->bow_jump_02,
                                        &tm->bow_jump_03,
                                        &tm->bow_jump_04,
                                        &tm->bow_jump_05,
                                },
                                6,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_CAST]
            = (AnimationConfig){{
                                        &tm->cast_00,
                                        &tm->cast_01,
                                        &tm->cast_02,
                                        &tm->cast_03,
                                },
                                4,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_CAST_LOOP]
            = (AnimationConfig){{
                                        &tm->cast_loop_00,
                                        &tm->cast_loop_01,
                                        &tm->cast_loop_02,
                                        &tm->cast_loop_03,
                                },
                                4,
                                0.10f,
                                true};

    animation_configs[ANIMATION_TYPE_CORNER_CLIMB]
            = (AnimationConfig){{
                                        &tm->corner_climb_00,
                                        &tm->corner_climb_01,
                                        &tm->corner_climb_02,
                                        &tm->corner_climb_03,
                                        &tm->corner_climb_04,
                                },
                                5,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_CORNER_GRAB]
            = (AnimationConfig){{
                                        &tm->corner_grab_00,
                                        &tm->corner_grab_01,
                                        &tm->corner_grab_02,
                                        &tm->corner_grab_03,
                                },
                                4,
                                0.10f,
                                true};

    animation_configs[ANIMATION_TYPE_CORNER_JUMP]
            = (AnimationConfig){{
                                        &tm->corner_jump_00,
                                        &tm->corner_jump_01,
                                },
                                2,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_CROUCH]
            = (AnimationConfig){{
                                        &tm->crouch_00,
                                        &tm->crouch_01,
                                        &tm->crouch_02,
                                        &tm->crouch_03,
                                },
                                4,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_CROUCH_WALK]
            = (AnimationConfig){{
                                        &tm->crouch_walk_00,
                                        &tm->crouch_walk_01,
                                        &tm->crouch_walk_02,
                                        &tm->crouch_walk_03,
                                        &tm->crouch_walk_04,
                                        &tm->crouch_walk_05,
                                },
                                6,
                                0.10f,
                                true};

    animation_configs[ANIMATION_TYPE_DIE]
            = (AnimationConfig){{
                                        &tm->die_00,
                                        &tm->die_01,
                                        &tm->die_02,
                                        &tm->die_03,
                                        &tm->die_04,
                                        &tm->die_05,
                                        &tm->die_06,
                                },
                                7,
                                0.12f,
                                false};

    animation_configs[ANIMATION_TYPE_DROP_KICK]
            = (AnimationConfig){{
                                        &tm->drop_kick_00,
                                        &tm->drop_kick_01,
                                        &tm->drop_kick_02,
                                        &tm->drop_kick_03,
                                },
                                4,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_FALL]
            = (AnimationConfig){{
                                        &tm->fall_00,
                                        &tm->fall_01,
                                },
                                2,
                                0.10f,
                                true};

    animation_configs[ANIMATION_TYPE_GET_UP]
            = (AnimationConfig){{
                                        &tm->get_up_00,
                                        &tm->get_up_01,
                                        &tm->get_up_02,
                                        &tm->get_up_03,
                                        &tm->get_up_04,
                                        &tm->get_up_05,
                                        &tm->get_up_06,
                                },
                                7,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_HURT]
            = (AnimationConfig){{
                                        &tm->hurt_00,
                                        &tm->hurt_01,
                                        &tm->hurt_02,
                                },
                                3,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_IDLE]
            = (AnimationConfig){{
                                        &tm->idle_00,
                                        &tm->idle_01,
                                        &tm->idle_02,
                                        &tm->idle_03,
                                },
                                4,
                                0.25f,
                                true};

    animation_configs[ANIMATION_TYPE_IDLE2]
            = (AnimationConfig){{
                                        &tm->idle2_00,
                                        &tm->idle2_01,
                                        &tm->idle2_02,
                                        &tm->idle2_03,
                                },
                                4,
                                0.25f,
                                true};

    animation_configs[ANIMATION_TYPE_ITEMS]
            = (AnimationConfig){{
                                        &tm->items_00,
                                        &tm->items_01,
                                        &tm->items_02,
                                },
                                3,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_JUMP]
            = (AnimationConfig){{
                                        &tm->jump_00,
                                        &tm->jump_01,
                                        &tm->jump_02,
                                        &tm->jump_03,
                                },
                                4,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_KICK]
            = (AnimationConfig){{
                                        &tm->kick_00,
                                        &tm->kick_01,
                                        &tm->kick_02,
                                        &tm->kick_03,
                                        &tm->kick_04,
                                        &tm->kick_05,
                                        &tm->kick_06,
                                        &tm->kick_07,
                                },
                                8,
                                0.07f,
                                false};

    animation_configs[ANIMATION_TYPE_KNOCK_DOWN]
            = (AnimationConfig){{
                                        &tm->knock_down_00,
                                        &tm->knock_down_01,
                                        &tm->knock_down_02,
                                        &tm->knock_down_03,
                                        &tm->knock_down_04,
                                        &tm->knock_down_05,
                                        &tm->knock_down_06,
                                },
                                7,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_LADDER_CLIMB]
            = (AnimationConfig){{
                                        &tm->ladder_climb_00,
                                        &tm->ladder_climb_01,
                                        &tm->ladder_climb_02,
                                        &tm->ladder_climb_03,
                                },
                                4,
                                0.12f,
                                true};

    animation_configs[ANIMATION_TYPE_PUNCH]
            = (AnimationConfig){{
                                        &tm->punch_00,
                                        &tm->punch_01,
                                        &tm->punch_02,
                                        &tm->punch_03,
                                        &tm->punch_04,
                                        &tm->punch_05,
                                        &tm->punch_06,
                                        &tm->punch_07,
                                        &tm->punch_08,
                                        &tm->punch_09,
                                        &tm->punch_10,
                                        &tm->punch_11,
                                        &tm->punch_12,
                                },
                                13,
                                0.05f,
                                false};

    animation_configs[ANIMATION_TYPE_RUN]
            = (AnimationConfig){{
                                        &tm->run_00,
                                        &tm->run_01,
                                        &tm->run_02,
                                        &tm->run_03,
                                        &tm->run_04,
                                        &tm->run_05,
                                },
                                6,
                                0.06f,
                                true};

    animation_configs[ANIMATION_TYPE_RUN2]
            = (AnimationConfig){{
                                        &tm->run2_00,
                                        &tm->run2_01,
                                        &tm->run2_02,
                                        &tm->run2_03,
                                        &tm->run2_04,
                                        &tm->run2_05,
                                },
                                6,
                                0.06f,
                                true};

    animation_configs[ANIMATION_TYPE_RUN_PUNCH]
            = (AnimationConfig){{
                                        &tm->run_punch_00,
                                        &tm->run_punch_01,
                                        &tm->run_punch_02,
                                        &tm->run_punch_03,
                                        &tm->run_punch_04,
                                        &tm->run_punch_05,
                                        &tm->run_punch_06,
                                },
                                7,
                                0.06f,
                                false};

    animation_configs[ANIMATION_TYPE_SLIDE]
            = (AnimationConfig){{
                                        &tm->slide_00,
                                        &tm->slide_01,
                                },
                                2,
                                0.10f,
                                false};

    animation_configs[ANIMATION_TYPE_SOMERSAULT]
            = (AnimationConfig){{
                                        &tm->somersault_00,
                                        &tm->somersault_01,
                                        &tm->somersault_02,
                                        &tm->somersault_03,
                                },
                                4,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_STAND]
            = (AnimationConfig){{
                                        &tm->stand_00,
                                        &tm->stand_01,
                                        &tm->stand_02,
                                },
                                3,
                                0.15f,
                                true};

    animation_configs[ANIMATION_TYPE_SWORD_DRAW]
            = (AnimationConfig){{
                                        &tm->sword_draw_00,
                                        &tm->sword_draw_01,
                                        &tm->sword_draw_02,
                                        &tm->sword_draw_03,
                                },
                                4,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_SWORD_SHEATHE]
            = (AnimationConfig){{
                                        &tm->sword_sheathe_00,
                                        &tm->sword_sheathe_01,
                                        &tm->sword_sheathe_02,
                                        &tm->sword_sheathe_03,
                                },
                                4,
                                0.08f,
                                false};

    animation_configs[ANIMATION_TYPE_WALK]
            = (AnimationConfig){{
                                        &tm->walk_00,
                                        &tm->walk_01,
                                        &tm->walk_02,
                                        &tm->walk_03,
                                        &tm->walk_04,
                                        &tm->walk_05,
                                },
                                6,
                                0.10f,
                                true};

    animation_configs[ANIMATION_TYPE_WALL_RUN]
            = (AnimationConfig){{
                                        &tm->wall_run_00,
                                        &tm->wall_run_01,
                                        &tm->wall_run_02,
                                        &tm->wall_run_03,
                                        &tm->wall_run_04,
                                        &tm->wall_run_05,
                                },
                                6,
                                0.07f,
                                true};

    animation_configs[ANIMATION_TYPE_WALL_SLIDE]
            = (AnimationConfig){{
                                        &tm->wall_slide_00,
                                        &tm->wall_slide_01,
                                },
                                2,
                                0.10f,
                                true};
}

void animation_set(Animation *animation, const int anim_type)
{
    assert(animation);

    if (animation->current_anim_type == anim_type)
        return;

    animation->current_anim_type = anim_type;
    animation->current_frame     = 0;
    animation->frame_timer       = 0.0f;
    animation->is_finished       = false;
}

void animation_update(
        Animation            *animation,
        const AnimationConfig animation_configs[ANIMATION_TYPE_MAX],
        const float           dt)
{
    assert(animation);

    if (animation->is_finished)
        return;

    const AnimationConfig *config
            = &animation_configs[animation->current_anim_type];

    animation->frame_timer += dt;
    if (animation->frame_timer >= config->frame_duration) {
        animation->frame_timer = 0.0f;
        animation->current_frame++;

        if (animation->current_frame >= config->frame_count) {
            if (config->loops) {
                animation->current_frame = 0;
            } else {
                animation->is_finished = true;
            }
        }
    }
}
