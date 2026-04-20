#include "player.h"
#include "settings.h"
#include <assert.h>
#include <raymath.h>
#include <stdlib.h>

static const Rectangle player_collider_db[P_STATE_MAX] = {
    [P_STATE_IDLE] = {.x = 22, .y = 12, .width = 12, .height = 32},
    [P_STATE_RUN] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_ATTACK] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_DEATH] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_HURT] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_JUMP] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_UPTO_FALL] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_FALL] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_EDGE_GRAB] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_EDGE_IDLE] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_WALL_SLIDE] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_CROUCH] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_DASH] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_DASH_ATTACK] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_SLIDE] = {.x = 10, .y = 10, .width = 50, .height = 50},
    [P_STATE_LADDER_GRAB] = {.x = 10, .y = 10, .width = 50, .height = 50},
};

static const Animation player_animation_db[P_STATE_MAX] = {

    [P_STATE_IDLE] = {SPRITE_IDLE_1, SPRITE_IDLE_6, 0.1f},
    [P_STATE_RUN] = {SPRITE_RUN_1, SPRITE_RUN_8, 0.1f},
    [P_STATE_ATTACK] = {SPRITE_ATTACK_1, SPRITE_ATTACK_12, 0.1f},
    [P_STATE_DEATH] = {SPRITE_DEATH_1, SPRITE_DEATH_11, 0.1f},
    [P_STATE_HURT] = {SPRITE_HURT_1, SPRITE_HURT_4, 0.1f},
    [P_STATE_JUMP] = {SPRITE_JUMP_1, SPRITE_JUMP_3, 0.1f},
    [P_STATE_UPTO_FALL] = {SPRITE_UPTO_FALL_1, SPRITE_UPTO_FALL_2, 0.1f},
    [P_STATE_FALL] = {SPRITE_FALL_1, SPRITE_FALL_3, 0.1f},
    [P_STATE_EDGE_GRAB] = {SPRITE_EDGE_GRAB_1, SPRITE_EDGE_GRAB_5, 0.1f},
    [P_STATE_EDGE_IDLE] = {SPRITE_EDGE_IDLE_1, SPRITE_EDGE_IDLE_6, 0.1f},
    [P_STATE_WALL_SLIDE] = {SPRITE_WALL_SLIDE_1, SPRITE_WALL_SLIDE_3, 0.1f},
    [P_STATE_CROUCH] = {SPRITE_CROUCH_1, SPRITE_CROUCH_6, 0.1f},
    [P_STATE_DASH] = {SPRITE_DASH_1, SPRITE_DASH_7, 0.1f},
    [P_STATE_DASH_ATTACK] = {SPRITE_DASH_ATTACK_1, SPRITE_DASH_ATTACK_10, 0.1f},
    [P_STATE_SLIDE] = {SPRITE_SLIDE_1, SPRITE_SLIDE_5, 0.1f},
    [P_STATE_LADDER_GRAB] = {SPRITE_LADDER_GRAB_1, SPRITE_LADDER_GRAB_8, 0.1f},
};

void player_init(Player *player)
{
    assert(player);

    player->current_state = P_STATE_IDLE;

    player->scale = 3.0f;
    const Animation *anim = &player_animation_db[player->current_state];
    player->source = sprite_db[anim->start_frame];

    const float width = player->source.width * player->scale;
    const float height = player->source.height * player->scale;
    const float x = 100.0f;
    const float y = MAP_SIZE - height;
    player->dest = (Rectangle){x, y, width, height};
    player->origin = (Vector2){player->dest.width / 2.0f,
                               player->dest.height / 2.0f};
    player->tint = WHITE;

    player->initial_h_speed = 300.0f;
    player->h_speed = player->initial_h_speed;
    player->dash_speed_max = 500.0f;
    player->dash_speed = 200.0f;
    player->v_speed = 0.0f;
    player->direction_x = 0.0f;

    player->jump_force = -500.0f;
    player->gravity = 1200.0f;

    player->frame_timer = 0.0f;
    player->frame_index = anim->start_frame;

    player->on_ground = true;
}

static Rectangle get_collider_offset(const Player *player)
{
    assert(player);

    Rectangle offset;

    switch (player->current_state) {
    case P_STATE_IDLE:
        offset = player_collider_db[P_STATE_IDLE];
        break;
    case P_STATE_RUN:
        offset = player_collider_db[P_STATE_RUN];
        break;
    case P_STATE_ATTACK:
        offset = player_collider_db[P_STATE_ATTACK];
        break;
    case P_STATE_DEATH:
        offset = player_collider_db[P_STATE_DEATH];
        break;
    case P_STATE_HURT:
        offset = player_collider_db[P_STATE_HURT];
        break;
    case P_STATE_JUMP:
        offset = player_collider_db[P_STATE_JUMP];
        break;
    case P_STATE_UPTO_FALL:
        offset = player_collider_db[P_STATE_UPTO_FALL];
        break;
    case P_STATE_FALL:
        offset = player_collider_db[P_STATE_FALL];
        break;
    case P_STATE_EDGE_GRAB:
        offset = player_collider_db[P_STATE_EDGE_GRAB];
        break;
    case P_STATE_EDGE_IDLE:
        offset = player_collider_db[P_STATE_EDGE_IDLE];
        break;
    case P_STATE_WALL_SLIDE:
        offset = player_collider_db[P_STATE_WALL_SLIDE];
        break;
    case P_STATE_CROUCH:
        offset = player_collider_db[P_STATE_CROUCH];
        break;
    case P_STATE_DASH:
        offset = player_collider_db[P_STATE_DASH];
        break;
    case P_STATE_DASH_ATTACK:
        offset = player_collider_db[P_STATE_DASH_ATTACK];
        break;
    case P_STATE_SLIDE:
        offset = player_collider_db[P_STATE_SLIDE];
        break;
    case P_STATE_LADDER_GRAB:
        offset = player_collider_db[P_STATE_LADDER_GRAB];
        break;
    default:
        offset = player_collider_db[P_STATE_IDLE];
        break;
    }

    return offset;
}

void player_draw(const Player *player, const Texture2D sheet)
{
    assert(player);

    DrawTexturePro(sheet, player->source, player->dest, player->origin,
                   player->rotation, player->tint);

    // sprite outline
    DrawRectangleLinesEx(player->collider, 2.0f, LIGHTGRAY);
}

static void horizontal_movement(Player *player, const float dt)
{
    assert(player);

    // handle input
    player->direction_x = (int) IsKeyDown(KEY_D) - (int) IsKeyDown(KEY_A);

    // move
    player->dest.x += player->direction_x * player->h_speed * dt;
}

static void vertical_movement(Player *player, const float dt)
{
    assert(player);

    // initiate jump
    if (IsKeyPressed(KEY_SPACE) && player->on_ground) {
        player->on_ground = false;
        player->v_speed = player->jump_force;
    }

    // jumping
    if (!player->on_ground) {
        player->v_speed += player->gravity * dt;
    }
    player->dest.y += player->v_speed * dt;

    // hit ground
    if (player->dest.y + player->origin.y >= MAP_SIZE) {
        player->dest.y = MAP_SIZE - player->origin.y;
        player->v_speed = 0.0f;
        player->on_ground = true;
    }
}

static void set_bounds(Player *player)
{
    assert(player);

    // set bounds
    player->dest.x = fmaxf(player->origin.x,
                           fminf(player->dest.x, MAP_SIZE - player->origin.x));
    player->dest.y = fmaxf(player->origin.y,
                           fminf(player->dest.y, MAP_SIZE - player->origin.y));
}

static PlayerState get_player_state(const Player *player)
{
    assert(player);

    const Animation *anim = NULL;

    // lock in dash animation
    anim = &player_animation_db[P_STATE_DASH];
    if (player->current_state == P_STATE_DASH &&
        player->frame_index < anim->end_frame) {
        //
        return P_STATE_DASH;
    }

    // lock in attack animation
    anim = &player_animation_db[P_STATE_ATTACK];
    if (player->current_state == P_STATE_ATTACK &&
        player->frame_index < anim->end_frame) {
        //
        return P_STATE_ATTACK;
    }

    if (!player->on_ground) {
        return (player->v_speed > 0) ? P_STATE_FALL : P_STATE_JUMP;
    }

    if (fabsf(player->direction_x) > 0.0f && IsKeyPressed(KEY_LEFT_SHIFT)) {
        return P_STATE_DASH;
    }

    if (player->on_ground && IsKeyPressed(KEY_E)) {
        return P_STATE_ATTACK;
    }

    if (fabsf(player->direction_x) > 0.0f) {
        return P_STATE_RUN;
    }

    return P_STATE_IDLE;
}

static void player_animation(Player *player, const PlayerState new_state,
                             const float dt)
{
    assert(player);

    const Animation *anim = &player_animation_db[new_state];

    // reset animation
    if (player->current_state != new_state) {
        player->current_state = new_state;
        player->frame_index = anim->start_frame;
        player->frame_timer = 0.0f;
    }

    // animation
    player->frame_timer += dt;
    if (player->frame_timer >= anim->frame_speed) {
        player->frame_timer = 0.0f;
        player->frame_index++;
        if (player->frame_index > anim->end_frame) {
            player->frame_index = anim->start_frame;
        }
    }
}

void player_update(Player *player, const float dt)
{
    assert(player);
    // set collider offset
    const Rectangle collider_offset = get_collider_offset(player);
    player->collider = (Rectangle){
        player->dest.x - player->origin.x + (collider_offset.x * player->scale),
        player->dest.y - player->origin.y + (collider_offset.y * player->scale),
        collider_offset.width * player->scale,
        collider_offset.height * player->scale,
    };

    if (player->current_state != P_STATE_ATTACK) {
        // dashing
        if (player->current_state == P_STATE_DASH) {
            player->h_speed = fminf(player->h_speed + player->dash_speed * dt,
                                    player->initial_h_speed +
                                        player->dash_speed_max);
        } else {
            const float easing_amount = 1.0f - expf(-8.0f * dt);
            player->h_speed = Lerp(player->h_speed, player->initial_h_speed,
                                   easing_amount);
        }

        horizontal_movement(player, dt);
        vertical_movement(player, dt);

        set_bounds(player);
    }

    const PlayerState new_state = get_player_state(player);
    player_animation(player, new_state, dt);

    // set source
    player->source = sprite_db[player->frame_index];
    player->source.width = (player->direction_x >= 0.0f)
                               ? fabsf(player->source.width)
                               : -fabsf(player->source.width);
}
