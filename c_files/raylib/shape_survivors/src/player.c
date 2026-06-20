#include "player.h"
#include "settings.h"
#include "systems.h"
#include <assert.h>
#include <raymath.h>

void player_init(Player* player) {
    assert(player);

    player->level.current = 1;

    player->xp.current          = 0;
    player->xp.next             = system_get_xp_next(&player->level);
    player->xp.pending_levelups = 0;

    player->position.x = MAP_SIZE / 2.0f;
    player->position.y = MAP_SIZE / 2.0f;

    player->rect.width  = 40.0f;
    player->rect.height = 40.0f;

    player->rotation.angle = 0.0f;

    player->color.tint = BLUE;

    player->text.text      = "P";
    player->text.font_size = 20.0f;
    player->text.spacing   = 0.0f;
    player->text.tint      = WHITE;

    player->move.speed     = 120.0f;
    player->move.direction = (Vector2){0, 0};

    player->health.max     = 100;
    player->health.current = 100;

    player->animation.max_hit_timer = 0.2f;
    player->animation.hit_timer     = 0.0f;

    player->bullet_config.damage   = 1;
    player->bullet_config.speed    = 300.0f;
    player->bullet_config.lifetime = 1.0f;

    player->bullet_timer.elapsed  = GetTime();
    player->bullet_timer.interval = 1.0f;
}

static void handle_input(Player* player) {
    assert(player);

    player->move.direction.x = (float) IsKeyDown(KEY_D) - (float) IsKeyDown(KEY_A);
    player->move.direction.y = (float) IsKeyDown(KEY_S) - (float) IsKeyDown(KEY_W);

    player->move.direction = Vector2Normalize(player->move.direction);
}

void player_update(Player* player, const float dt) {
    assert(player);

    handle_input(player);
    system_move(&player->position, &player->move, dt);
    system_set_bounds(&player->position, &player->rect, (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(&player->animation, dt);
}

void player_draw(const Player* player) {
    assert(player);

    system_draw_rect(
        &player->position, &player->rect, &player->rotation, &player->color, &player->animation);
    system_draw_centered_text(
        &player->position, player->rect.width / 2.0f, player->rect.height / 2.0f, &player->text);
}
