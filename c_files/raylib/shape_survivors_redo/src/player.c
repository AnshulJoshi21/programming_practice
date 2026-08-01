#include "bullets/bullet_orbital.h"
#include "bullets/bullet_projectile.h"
#include "player.h"
#include "settings.h"
#include "utils.h"
#include <assert.h>
#include <raymath.h>

void player_init(Player* player) {
    assert(player);

    player->pos       = (Vector2){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f};
    player->origin    = (Vector2){PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f};
    player->rotation  = 0.0f;
    player->color     = BLUE;
    player->speed     = PLAYER_SPEED;
    player->direction = (Vector2){0, 0};
    player->hp        = PLAYER_MAX_HP;
    player->hit_timer = 0.0f;

    player->weapons[0].weapon.magic_missiles = (EntityConfig){.type = PROJECTILE_TYPE_MAGIC_MISSILE,
                                                              .pattern = BULLET_PATTERN_PROJECTILE,
                                                              .level   = 1,
                                                              .homing  = false};
    player->weapons[1].weapon.orbiting_orbs  = (EntityConfig){.type    = ORBITAL_TYPE_ORBITING_ORBS,
                                                              .pattern = BULLET_PATTERN_ORBITAL,
                                                              .level   = 1,
                                                              .homing  = false};
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
    player->pos.x += player->direction.x * player->speed * dt;
    player->pos.y += player->direction.y * player->speed * dt;

    // bounds
    player->pos.x = Clamp(player->pos.x, player->origin.x, MAP_SIZE - player->origin.x);
    player->pos.y = Clamp(player->pos.y, player->origin.y, MAP_SIZE - player->origin.y);
}

void player_draw(const Player* player) {
    assert(player);
    const Rectangle dest = (Rectangle){player->pos.x, player->pos.y, PLAYER_SIZE, PLAYER_SIZE};

    DrawRectanglePro(dest, player->origin, player->rotation, player->color);
    utils_draw_centered_text(ORIGIN_TYPE_CENTER, "P", dest, 20.0f, 0.0f, WHITE);
}
