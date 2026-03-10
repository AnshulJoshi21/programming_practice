#include "../include/player.h"
#include "../include/settings.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

static const float PLAYER_SCALE_OFFSET = 0.7f;

void player_init(Player *player)
{
    assert(player);

    player->sprite_name = SPRITE_SHIP_A;

    const Rectangle source = sprite_db[player->sprite_name];
    player->dest           = (Rectangle){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f,
                                         source.width * PLAYER_SCALE_OFFSET,
                                         source.height * PLAYER_SCALE_OFFSET};
    player->origin =
        (Vector2){player->dest.width / 2.0f, player->dest.height / 2.0f};
    player->rotation = ROTATION_OFFSET;
    player->tint     = WHITE;

    player->speed     = 300.0f;
    player->direction = (Vector2){0, 0};

    player->max_hp = 100.0f;
    player->hp     = player->hp;
}

void player_draw(const Player *player, const Texture2D spritesheet)
{
    assert(player);

    const Rectangle source = sprite_db[player->sprite_name];

    DrawTexturePro(spritesheet, source, player->dest, player->origin,
                   player->rotation, player->tint);
}

void player_handle_input(Player *player)
{
    assert(player);

    player->direction.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
    player->direction.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);

    player->direction = Vector2Normalize(player->direction);
}

void player_rotate(Player *player, const Vector2 target_pos)
{
    assert(player);

    float dx         = target_pos.x - player->dest.x;
    float dy         = target_pos.y - player->dest.y;
    player->rotation = atan2f(dy, dx) * RAD2DEG + ROTATION_OFFSET;
}

void player_move(Player *player, const float dt)
{
    assert(player);

    player->dest.x += player->direction.x * player->speed * dt;
    player->dest.y += player->direction.y * player->speed * dt;
}

void player_bounds(Player *player)
{
    assert(player);

    player->dest.x =
        fmaxf(player->dest.width / 2.0f,
              fminf(player->dest.x, MAP_SIZE - player->dest.width / 2.0f));

    player->dest.y =
        fmaxf(player->dest.height / 2.0f,
              fminf(player->dest.y, MAP_SIZE - player->dest.height / 2.0f));
}

// target_pos = closest enemy
void player_update(Player *player, const float dt, const Vector2 target_pos)
{
    assert(player);

    player_handle_input(player);
    player_rotate(player, target_pos);
    player_move(player, dt);
    player_bounds(player);
}
