#include "player.h"
#include "settings.h"
#include "utils.h"
#include <assert.h>
#include <raymath.h>

static int get_xp_next(const Player* player) {
    assert(player);

    return 10 + (player->level * player->level * 2);
}

void player_init(Player* player) {
    assert(player);

    player->level   = 1;
    player->xp      = 0;
    player->xp_next = get_xp_next(player);

    const float size  = 40.0f;
    player->rect      = (Rectangle){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f, size, size};
    player->origin    = (Vector2){player->rect.width / 2.0f, player->rect.height / 2.0f};
    player->rotation  = 0.0f;
    player->color     = BLUE;
    player->speed     = 120.0f;
    player->direction = (Vector2){0, 0};

    player->max_hp = 100;
    player->hp     = player->max_hp;

    player->bullet_timer = (Timer){.elapsed = 0.0f, .duration = 1.0f};
}

static void handle_input(Player* player) {
    assert(player);

    player->direction.x = (float) IsKeyDown(KEY_D) - (float) IsKeyDown(KEY_A);
    player->direction.y = (float) IsKeyDown(KEY_S) - (float) IsKeyDown(KEY_W);

    player->direction = Vector2Normalize(player->direction);
}

void player_update(Player* player, const float dt) {
    assert(player);

    handle_input(player);

    // move
    player->rect.x += player->direction.x * player->speed * dt;
    player->rect.y += player->direction.y * player->speed * dt;

    // set bounds
    player->rect.x = fmaxf(player->origin.x, fminf(player->rect.x, MAP_SIZE - player->origin.x));
    player->rect.y = fmaxf(player->origin.y, fminf(player->rect.y, MAP_SIZE - player->origin.y));
}

void player_draw(const Player* player) {
    assert(player);

    DrawRectanglePro(player->rect, player->origin, player->rotation, player->color);

    draw_centered_text(ORIGIN_TYPE_CENTER, "P", player->rect, 20.0f, 0.0f, WHITE);
}
