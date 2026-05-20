#include "input.h"
#include "player.h"
#include "settings.h"

#include <assert.h>
#include <math.h>

void player_init(Player               *player,
                 const AnimationConfig animation_config[ANIMATION_TYPE_MAX])
{
    assert(player);

    player->animation_config = animation_config;

    player->state        = PLAYER_STATE_IDLE;
    player->prev_state   = player->state;
    player->state_locked = false;

    player->scale  = (Vector2){3.0f, 3.0f};
    player->source = (Rectangle){0, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
    player->dest   = (Rectangle){SPRITE_WIDTH,
                                 MAP_HEIGHT - SPRITE_HEIGHT,
                                 player->source.width * player->scale.x,
                                 player->source.height * player->scale.y};
    player->origin
            = (Vector2){player->dest.width / 2.0f, player->dest.height / 2.0f};
    player->rotation = 0.0f;
    player->tint     = WHITE;

    player->direction = (Vector2){0, 0};

    player->speed_horizontal     = 300.0f;
    player->speed_vertical       = 0.0f;
    player->run_speed_multiplier = 2.0f;

    player->jump_force = -600.0f;
    player->gravity    = 1200.0f;

    player->can_jump    = true;
    player->facing_left = false;

    player->animation = (Animation){.current_anim_type = ANIMATION_TYPE_IDLE,
                                    0,
                                    0.0f,
                                    false};

    // set keybindings
    player->input_map[ACTION_MOVE_LEFT].key  = KEY_A;
    player->input_map[ACTION_MOVE_RIGHT].key = KEY_D;
    player->input_map[ACTION_JUMP].key       = KEY_SPACE;
    player->input_map[ACTION_RUN].key        = KEY_LEFT_SHIFT;
    player->input_map[ACTION_ATTACK].key     = KEY_E;
}

static AnimationType player_get_animation(Player *player)
{
    switch (player->state) {
        case PLAYER_STATE_ATTACK:
            return ANIMATION_TYPE_ATTACK1;
        case PLAYER_STATE_CAST:
            return ANIMATION_TYPE_CAST;
        case PLAYER_STATE_CLIMB:
            return ANIMATION_TYPE_CORNER_CLIMB;
        case PLAYER_STATE_CROUCH:
            return ANIMATION_TYPE_CROUCH;
        case PLAYER_STATE_DIE:
            return ANIMATION_TYPE_DIE;
        case PLAYER_STATE_FALL:
            return ANIMATION_TYPE_FALL;
        case PLAYER_STATE_HURT:
            return ANIMATION_TYPE_HURT;
        case PLAYER_STATE_IDLE:
            return ANIMATION_TYPE_IDLE;
        case PLAYER_STATE_JUMP:
            return ANIMATION_TYPE_JUMP;
        case PLAYER_STATE_RUN:
            return ANIMATION_TYPE_RUN;
        case PLAYER_STATE_SLIDE:
            return ANIMATION_TYPE_SLIDE;
        case PLAYER_STATE_SOMERSAULT:
            return ANIMATION_TYPE_SOMERSAULT;
        case PLAYER_STATE_WALK:
            return ANIMATION_TYPE_WALK;

        default:
            return ANIMATION_TYPE_IDLE;
    }
}

void player_set_state(Player *player, const PlayerState new_state)
{
    if (player->state_locked)
        return;

    if (player->state == new_state)
        return;

    player->prev_state = player->state;
    player->state      = new_state;

    player->state_locked = (player->animation_config->loops) ? false : true;

    if (player->speed_vertical > 0)
        player->state = PLAYER_STATE_FALL;

    animation_set(&player->animation, player_get_animation(player));
}

static void player_handle_input(Player *player)
{
    assert(player);

    // horizontal movement
    if (player->state == PLAYER_STATE_IDLE) {
        if (input_map_is_key_down(player->input_map, ACTION_MOVE_LEFT)
            || input_map_is_key_down(player->input_map, ACTION_MOVE_RIGHT)) {
            //
            player_set_state(player, PLAYER_STATE_WALK);
        }

        if (input_map_is_key_down(player->input_map, ACTION_MOVE_LEFT)) {
            //
            player->facing_left = true;
        }
        if (input_map_is_key_down(player->input_map, ACTION_MOVE_RIGHT)) {
            //
            player->facing_left = false;
        }
    }
    // running
    if (player->state == PLAYER_STATE_WALK) {
        if (input_map_is_key_down(player->input_map, ACTION_RUN)) {
            //
            player_set_state(player, PLAYER_STATE_RUN);
        }
    }
    // jumping
    if (input_map_is_key_pressed(player->input_map, ACTION_JUMP)
        && player->can_jump) {
        //
        player_set_state(player, PLAYER_STATE_JUMP);
        player->speed_vertical = player->jump_force;
    }

    // attack
    if (input_map_is_key_pressed(player->input_map, ACTION_ATTACK)) {
        player_set_state(player, PLAYER_STATE_ATTACK);
    }
}

static void player_state_management(Player *player, const float dt)
{
    assert(player);

    switch (player->state) {
        case PLAYER_STATE_ATTACK:
            break;
        case PLAYER_STATE_CAST:
            break;
        case PLAYER_STATE_CLIMB:
            break;
        case PLAYER_STATE_CROUCH:
            break;
        case PLAYER_STATE_DIE:
            break;
        case PLAYER_STATE_FALL:
            break;
        case PLAYER_STATE_HURT:
            break;
        case PLAYER_STATE_IDLE:
            break;
        case PLAYER_STATE_JUMP:
            player->can_jump = false;
            player->speed_vertical += player->gravity * dt;
            player->dest.y += player->speed_vertical * dt;
            break;
        case PLAYER_STATE_RUN:
            break;
        case PLAYER_STATE_SLIDE:
            break;
        case PLAYER_STATE_SOMERSAULT:
            break;
        case PLAYER_STATE_WALK:

            break;
        default:
            break;
    }
}

void player_update(Player *player, const float dt)
{
    assert(player);

    // initiate jump
    if (input_map_is_key_pressed(player->input_map, ACTION_JUMP)
        && player->can_jump) {
        player->speed_vertical = player->jump_force;
        player->can_jump       = false;
        animation_set(&player->animation, ANIMATION_TYPE_JUMP);
    }

    // jumping
    player->speed_vertical += player->gravity * dt;
    player->dest.y += player->speed_vertical * dt;

    // hit ground
    if (player->dest.y + player->origin.y >= MAP_HEIGHT) {
        player->speed_vertical = 0.0f;
        player->can_jump       = true;
    }

    // move
    player->dest.x += player->direction.x * player->speed_horizontal
                    * player->run_speed_multiplier * dt;
    player->dest.y += player->direction.y * player->speed_vertical * dt;

    // set bounds
    player->dest.x = fmaxf(player->origin.x,
                           fminf(player->dest.x, MAP_WIDTH - player->origin.x));
    player->dest.y
            = fmaxf(player->origin.y,
                    fminf(player->dest.y, MAP_HEIGHT - player->origin.y));

    // update sprite rects
    player->source.width = (player->facing_left) ? -SPRITE_WIDTH : SPRITE_WIDTH;
    player->dest.width   = player->source.width * player->scale.x;

    // animation
    animation_update(&player->animation, player->animation_config, dt);
}

void player_draw(const Player *player)
{
    assert(player);

    const AnimationConfig *config       = player->animation_config;
    const Animation       *current_anim = &player->animation;

    DrawTexturePro(*config->frames[current_anim->current_frame],
                   player->source,
                   player->dest,
                   player->origin,
                   player->rotation,
                   player->tint);
}
