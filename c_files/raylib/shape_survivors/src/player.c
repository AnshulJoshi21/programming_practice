#include "player.h"
#include "settings.h"
#include "systems.h"
#include <assert.h>
#include <raymath.h>

void player_init(Player* player) {
    assert(player);

    player->level.current = 1;
    player->level.pending = 0;

    player->xp.current = 0;
    player->xp.next    = system_get_xp_next(&player->level);

    player->position.x = MAP_SIZE / 2.0f;
    player->position.y = player->position.x;

    player->rect.width  = 40.0f;
    player->rect.height = player->rect.width;

    player->rotation.angle = 0.0f;

    player->color.tint = BLUE;

    player->text.string    = "P";
    player->text.font_size = 20.0f;
    player->text.spacing   = 0.0f;
    player->text.tint      = WHITE;

    player->movement.speed     = 120.0f;
    player->movement.direction = (Vector2){0, 0};

    player->health.max     = 100;
    player->health.current = player->health.max;

    player->animation.hit_timer_max     = 0.2f;
    player->animation.hit_timer_current = 0.0f;

    player->bullet_timer.elapsed  = GetTime();
    player->bullet_timer.interval = 1.0f;

    player->bullet_config.damage   = 1;
    player->bullet_config.speed    = 300.0f;
    player->bullet_config.lifetime = 1.0f;
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
    system_update_xp(&player->level, &player->xp);
    system_move(&player->position, &player->movement, dt);
    system_set_bounds(&player->position,
                      player->rect.width / 2.0f,
                      player->rect.height / 2.0f,
                      (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(&player->animation, dt);
    system_update_health(&player->health);
}

void player_draw(const Player* player) {
    assert(player);

    system_draw_rect(
        &player->position, &player->rect, &player->rotation, &player->color, &player->animation);

    system_draw_centered_text(
        &player->position, player->rect.width, player->rect.height, &player->text);
}
