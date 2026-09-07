#include "../settings.h"
#include "../utils.h"
#include "enemy.h"
#include <assert.h>
#include <raymath.h>

static Color get_random_darK_color(void) {
    const int random_num = GetRandomValue(1, 5);
    switch (random_num) {
        case 1:
            return DARKBLUE;
        case 2:
            return DARKBROWN;
        case 3:
            return DARKGRAY;
        case 4:
            return DARKGREEN;
        case 5:
            return DARKPURPLE;
        default:
            return DARKBLUE;
    }
}

void enemy_init(Enemy* enemy, const Vector2 target_pos) {
    assert(enemy);

    const float random_angle = randf(0, 2 * PI);
    const float random_distance
        = randf(GetScreenWidth() / 2.0f + 100.0f, GetScreenWidth() / 2.0f + 200.0f);

    const Vector2 start_pos = (Vector2){
        cosf(random_angle) * random_distance + target_pos.x,
        sinf(random_angle) * random_distance + target_pos.y,
    };

    const float size = 45.0f;
    enemy->rect      = (Rectangle){start_pos.x, start_pos.y, size, size};
    enemy->origin    = (Vector2){enemy->rect.width / 2.0f, enemy->rect.height / 2.0f};
    enemy->rotation  = 0.0f;
    enemy->color     = get_random_darK_color();
    enemy->speed     = 100.0f;
    enemy->direction = (Vector2){0, 0};

    enemy->max_hp = 5;
    enemy->hp     = enemy->max_hp;
    enemy->damage = 1;
}

void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos) {
    assert(enemy);

    // set direction
    const float dx       = target_pos.x - enemy->rect.x;
    const float dy       = target_pos.y - enemy->rect.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) {
        enemy->direction = (Vector2){dx / distance, dy / distance};

        // move
        enemy->rect.x += enemy->direction.x * enemy->speed * dt;
        enemy->rect.y += enemy->direction.y * enemy->speed * dt;

        // set bounds
        enemy->rect.x = fmaxf(enemy->origin.x, fminf(enemy->rect.x, MAP_SIZE - enemy->origin.x));
        enemy->rect.y = fmaxf(enemy->origin.y, fminf(enemy->rect.y, MAP_SIZE - enemy->origin.y));
    }
}

void enemy_draw(const Enemy* enemy) {
    assert(enemy);

    DrawRectanglePro(enemy->rect, enemy->origin, enemy->rotation, enemy->color);

    draw_centered_text(ORIGIN_TYPE_CENTER, "E", enemy->rect, 20.0f, 0.0f, WHITE);
}
