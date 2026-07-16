#include "animation_data.h"
#include "player.h"
#include "settings.h"
#include "systems.h"
#include <assert.h>
#include <raymath.h>

static const float            PLAYER_SCALE             = 2.5f;
static const WarriorAnimation PLAYER_INITIAL_ANIMATION = WARRIOR_ANIMATION_IDLE;
static const PlayerState      PLAYER_INITIAL_STATE     = PLAYER_STATE_IDLE;
static const float            PLAYER_SPEED_X           = 250.0f;
static const int              PLAYER_MAX_HEALTH        = 100;

void player_init(Player* player, const AssetManager* asset_manager) {
    assert(player);

    player->state.active  = true;
    player->state.prev    = PLAYER_INITIAL_STATE;
    player->state.current = PLAYER_INITIAL_STATE;

    player->level.current = 1;

    player->xp.current          = 0;
    player->xp.next             = system_get_xp_next(&player->level);
    player->xp.pending_levelups = 0;

    player->transform.pos      = (Vector2){0, 0};
    player->transform.scale    = (Vector2){PLAYER_SCALE, PLAYER_SCALE};
    player->transform.rotation = 0.0f;

    player->render.texture = asset_manager->warrior_sheet;
    player->render.source  = warrior_animation_configs[PLAYER_INITIAL_ANIMATION].frames[0];
    player->render.size    = (Vector2){player->render.source.width * player->transform.scale.x,
                                       player->render.source.height * player->transform.scale.y};
    player->render.origin  = (Vector2){player->render.size.x / 2.0f, player->render.size.y / 2.0f};
    player->render.tint    = WHITE;

    player->movement.speed_x   = PLAYER_SPEED_X;
    player->movement.speed_y   = 0.0f;
    player->movement.direction = (Vector2){0, 0};

    player->health.max     = PLAYER_MAX_HEALTH;
    player->health.current = player->health.max;

    player->animation.type        = PLAYER_INITIAL_ANIMATION;
    player->animation.current     = 0;
    player->animation.timer       = 0.0f;
    player->animation.is_finished = false;
}

static void set_animation(Player* player) {
    assert(player);

    switch (player->state.current) {
        case PLAYER_STATE_IDLE:
            player->animation.type = WARRIOR_ANIMATION_IDLE;
            break;
        case PLAYER_STATE_RUN:
            player->animation.type = WARRIOR_ANIMATION_RUN;
            break;
        case PLAYER_STATE_JUMP:
            if (player->movement.speed_y < 0)
                player->animation.type = WARRIOR_ANIMATION_JUMP;
            else if (player->movement.speed_y == 0)
                player->animation.type = WARRIOR_ANIMATION_UPTO_FALL;
            else if (player->movement.speed_y > 0)
                player->animation.type = WARRIOR_ANIMATION_FALL;
            break;
        case PLAYER_STATE_ATTACK:
            player->animation.type = WARRIOR_ANIMATION_TWO_COMBO_ATTACK;
            break;
        case PLAYER_STATE_HURT:
            player->animation.type = WARRIOR_ANIMATION_HURT;
            break;
        case PLAYER_STATE_DASH:
            player->animation.type = WARRIOR_ANIMATION_DASH;
            break;
        case PLAYER_STATE_SLIDE:
            player->animation.type = WARRIOR_ANIMATION_SLIDE;
            break;
        case PLAYER_STATE_CROUCH:
            player->animation.type = WARRIOR_ANIMATION_CROUCH;
            break;
        case PLAYER_STATE_LEDGE_HANG:
            player->animation.type = WARRIOR_ANIMATION_EDGE_GRAB;
            break;
        case PLAYER_STATE_WALL_SLIDE:
            player->animation.type = WARRIOR_ANIMATION_SLIDE;
            break;
        case PLAYER_STATE_LADDER:
            player->animation.type = WARRIOR_ANIMATION_LADDER_GRAB;
            break;
        case PLAYER_STATE_DEATH:
            player->animation.type = WARRIOR_ANIMATION_DEATH;
            break;

        default:
            player->animation.type = WARRIOR_ANIMATION_IDLE;
            break;
    }
}

static void handle_input(Player* player) {
    assert(player);

    player->movement.direction.x = (float) IsKeyDown(KEY_D) - (float) IsKeyDown(KEY_A);
    player->movement.direction.y = (float) IsKeyDown(KEY_S) - (float) IsKeyDown(KEY_W);

    player->movement.direction = Vector2Normalize(player->movement.direction);
}

void player_update(Player* player, const float dt) {
    assert(player);

    handle_input(player);
    system_move_x(&player->transform, &player->movement, dt);

    system_update_xp(&player->level, &player->xp);
    system_update_health(&player->health);

    set_animation(player);
    system_animate(ENTITY_WARRIOR, &player->animation, dt);

    system_update_dimenions(
        ENTITY_WARRIOR, &player->transform, &player->render, &player->animation);
    system_set_bounds(&player->transform, &player->render, (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
}

void player_draw(const Player* player) {
    assert(player);

    system_render_texture(&player->transform, &player->render);
}
