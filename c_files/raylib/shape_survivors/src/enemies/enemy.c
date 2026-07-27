#include "../settings.h"
#include "../systems.h"
#include "../utils.h"
#include "enemy.h"
#include <assert.h>
#include <raymath.h>

static Color get_random_dark_color(void) {
    int random_num = GetRandomValue(1, 5);

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

    const float random_angle = utils_randf(0, 2 * PI);
    const float random_distance
        = utils_randf(GetScreenWidth() / 2.0f, GetScreenWidth() / 2.0f + 100.0f);

    enemy->position.x = cosf(random_angle) * random_distance + target_pos.x;
    enemy->position.y = sinf(random_angle) * random_distance + target_pos.y;

    enemy->rect.width  = 45.0f;
    enemy->rect.height = enemy->rect.width;

    enemy->rotation.angle = 0.0f;

    enemy->color.tint = get_random_dark_color();

    enemy->text.string    = "E";
    enemy->text.font_size = 20.0f;
    enemy->text.spacing   = 0.0f;
    enemy->text.tint      = WHITE;

    enemy->movement.speed     = 100.0f;
    enemy->movement.direction = (Vector2){0, 0};

    enemy->health.max     = 5;
    enemy->health.current = enemy->health.max;

    enemy->damage.current = 1;

    enemy->animation.hit_timer_max     = 0.1f;
    enemy->animation.hit_timer_current = 0.0f;
}

void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos) {
    assert(enemy);

    system_set_direction(&enemy->position, &enemy->movement, target_pos);
    system_move(&enemy->position, &enemy->movement, dt);
    system_set_bounds(&enemy->position,
                      enemy->rect.width / 2.0f,
                      enemy->rect.height / 2.0f,
                      (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(&enemy->animation, dt);
    system_update_health(&enemy->health);
}

void enemy_draw(const Enemy* enemy) {
    assert(enemy);

    system_draw_rect(
        &enemy->position, &enemy->rect, &enemy->rotation, &enemy->color, &enemy->animation);

    system_draw_centered_text(
        &enemy->position, enemy->rect.width, enemy->rect.height, &enemy->text);
}
