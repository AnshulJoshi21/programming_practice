#include "player.h"
#include "settings.h"
#include "systems.h"
#include <assert.h>
#include <raymath.h>

void player_init(Player* player) {
    assert(player);

    player->level = (CLevel){
        .level = 1,
    };

    player->xp = (CXp){
        .xp               = 0,
        .xp_next          = system_get_xp_next(&player->level),
        .pending_levelups = 0,
    };

    player->position = (CPosition){
        .x = MAP_SIZE / 2.0f,
        .y = MAP_SIZE / 2.0f,
    };

    player->rotation = (CRotation){
        .angle = 0.0f,
    };

    player->rect = (CRect){
        .width  = 40.0f,
        .height = 40.0f,
    };

    player->color = (CColor){
        .tint = BLUE,
    };

    player->text = (CText){
        .text      = "P",
        .font_size = 20.0f,
        .spacing   = 0.0f,
        .tint      = WHITE,
    };

    player->move = (CMove){
        .speed     = 120.0f,
        .direction = (Vector2){0, 0},
    };

    player->health = (CHealth){
        .hp  = 100,
        .max = 100,
    };

    player->animation = (CAnimation){
        .hit_timer     = 0.0f,
        .hit_timer_max = 0.2f,
    };

    player->bullet_timer = (CTimer){
        .elapsed  = GetTime(),
        .duration = 1.0f,
    };
}

void player_draw(const Player* player) {
    assert(player);

    system_draw_rect(
        &player->position, &player->rect, &player->rotation, &player->animation, &player->color);
    system_draw_centered_text(
        &player->text,
        (Rectangle){
            player->position.x, player->position.y, player->rect.width, player->rect.height});
}

static void handle_input(Player* player) {
    assert(player);

    player->move.direction.x = (int) IsKeyDown(KEY_D) - (int) IsKeyDown(KEY_A);
    player->move.direction.y = (int) IsKeyDown(KEY_S) - (int) IsKeyDown(KEY_W);

    player->move.direction = Vector2Normalize(player->move.direction);
}

void player_update(Player* player, const float dt) {
    assert(player);

    handle_input(player);
    system_move(&player->position, &player->move, dt);
    system_set_bounds(&player->position, &player->rect, (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(&player->animation, dt);
}
