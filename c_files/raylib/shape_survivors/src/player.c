#include "player.h"
#include "settings.h"
#include "systems.h"

#include <assert.h>
#include <raymath.h>

void player_init(Player *player) {
    assert(player);

    player->xp.level = 1;
    player->xp.xp = 0;
    player->xp.xp_next = system_xp_to_next_level(&player->xp);
    player->xp.pending_levelups = 0;

    player->position.x = MAP_SIZE / 2.0f;
    player->position.y = MAP_SIZE / 2.0f;

    player->rect.width = 40.0f;
    player->rect.height = 40.0f;

    player->rotation.value = 0.0f;

    player->color.tint = BLUE;

    player->text.text = "@";

    player->move.speed = 120.0f;
    player->move.direction = (Vector2){0, 0};

    player->health.max_hp = 100;
    player->health.hp = player->health.max_hp;

    player->animation.hit_timer = 0.0f;

    player->bullet_timer.elapsed = GetTime();
    player->bullet_timer.interval = 1.0f;

    player->bullet_config.speed = 300.0f;
    player->bullet_config.damage = 1;
    player->bullet_config.lifetime = 1.0f;
}

void player_draw(const Player *player) {
    assert(player);

    system_draw_rect(&player->position, &player->rect, &player->rotation, &player->color,
                     &player->text, &player->animation);
    system_draw_hp_bar(ORIGIN_CENTER, &player->position, &player->rect, &player->health);
}

static void _handle_input(Player *player) {
    assert(player);

    player->move.direction.x = (int) IsKeyDown(KEY_D) - (int) IsKeyDown(KEY_A);
    player->move.direction.y = (int) IsKeyDown(KEY_S) - (int) IsKeyDown(KEY_W);

    player->move.direction = Vector2Normalize(player->move.direction);
}

void player_update(Player *player, const float dt) {
    assert(player);

    _handle_input(player);
    system_move(&player->position, &player->move, dt);
    system_set_bounds_rect(&player->position, &player->rect, (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(&player->animation, dt);
}
