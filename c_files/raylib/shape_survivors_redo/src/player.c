#include "player.h"
#include "settings.h"
#include "utils.h"
#include <assert.h>
#include <raymath.h>

void player_init(Player* player) {
    assert(player);

    player->rect = (Rectangle){
        MAP_SIZE / 2.0f,
        MAP_SIZE / 2.0f,
        PLAYER_SIZE,
        PLAYER_SIZE,
    };
    player->origin    = (Vector2){PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f};
    player->rotation  = 0.0f;
    player->color     = BLUE;
    player->speed     = PLAYER_SPEED;
    player->direction = (Vector2){0, 0};
    player->hp        = PLAYER_MAX_HP;
    player->hit_timer = 0.0f;
}

static void handle_input(Player* player) {
    assert(player);

    player->direction.x = (float) IsKeyDown(KEY_D) - (float) IsKeyDown(KEY_A);
    player->direction.y = (float) IsKeyDown(KEY_S) - (float) IsKeyDown(KEY_W);
    player->direction   = Vector2Normalize(player->direction);
}

void player_update(Player* player, const float dt) {
    assert(player);

    handle_input(player);

    // move
    player->rect.x += player->direction.x * player->speed * dt;
    player->rect.y += player->direction.y * player->speed * dt;

    // bounds
    player->rect.x = Clamp(player->rect.x, player->origin.x, MAP_SIZE - player->origin.x);
    player->rect.y = Clamp(player->rect.y, player->origin.y, MAP_SIZE - player->origin.y);
}

void player_draw(const Player* player) {
    assert(player);

    DrawRectanglePro(player->rect, player->origin, player->rotation, player->color);

    utils_draw_centered_text(ORIGIN_TYPE_CENTER, "P", player->rect, 20.0f, 0.0f, WHITE);
}
