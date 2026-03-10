#include "../include/player.h"
#include "../include/settings.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

static const float PLAYER_TEXTURE_SCALE = 0.7f;

void player_init(Player *player, const Texture2D spritesheet)
{
    assert(player);

    player->texture        = spritesheet;
    player->current_sprite = SPRITE_SHIP_A;
    player->source         = sprite_db[player->current_sprite];
    player->dest           = (Rectangle){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f,
                                         player->source.width * PLAYER_TEXTURE_SCALE,
                                         player->source.height * PLAYER_TEXTURE_SCALE};
    player->origin =
        (Vector2){player->dest.width / 2.0f, player->dest.height / 2.0f};
    player->rotation = ROTATION_OFFSET;
    player->tint     = WHITE;

    player->speed          = 300.0f;
    player->look_direction = (Vector2){0, 0};
    player->move_direction = (Vector2){0, 0};

    player->max_hp = 100.0f;
    player->hp     = player->max_hp;
}

void player_draw(const Player *player)
{
    assert(player);

    DrawTexturePro(player->texture, player->source, player->dest,
                   player->origin, player->rotation, player->tint);
}

static void player_handle_input(Player *player)
{
    assert(player);

    player->move_direction.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
    player->move_direction.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);

    player->move_direction = Vector2Normalize(player->move_direction);
}

static void player_rotate(Player *player, const Vector2 closest_target)
{
    assert(player);

    player->look_direction.x = closest_target.x - player->dest.x;
    player->look_direction.y = closest_target.y - player->dest.y;

    player->rotation =
        atan2f(player->look_direction.y, player->look_direction.x) * RAD2DEG +
        ROTATION_OFFSET;
}

static void player_move(Player *player, const float dt)
{
    assert(player);

    player->dest.x += player->move_direction.x * player->speed * dt;
    player->dest.y += player->move_direction.y * player->speed * dt;
}

static void player_bounds(Player *player)
{
    assert(player);

    player->dest.x =
        fmaxf(player->dest.width / 2.0f,
              fminf(player->dest.x, MAP_SIZE - player->dest.width / 2.0f));

    player->dest.y =
        fmaxf(player->dest.height / 2.0f,
              fminf(player->dest.y, MAP_SIZE - player->dest.height / 2.0f));
}

void player_update(Player *player, const float dt, const Vector2 closest_target)
{
    assert(player);

    player_handle_input(player);
    player_rotate(player, closest_target);
    player_move(player, dt);
    player_bounds(player);
}
