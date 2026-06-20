#include "../settings.h"
#include "../systems.h"
#include "../utils.h"
#include "enemy.h"
#include <assert.h>
#include <math.h>

void enemy_init(Enemy* enemy, const int current_wave, const Vector2 target_pos) {
    assert(enemy);

    const float random_angle = randf(0, 2 * PI);
    const float random_distance
        = randf(GetScreenWidth() / 2.0f + 100.0f, GetScreenHeight() / 2.0f + 200.0f);
    const Vector2 start_pos = (Vector2){
        cosf(random_angle) * random_distance + target_pos.x,
        sinf(random_angle) * random_distance + target_pos.y,
    };

    enemy->level.current = current_wave;

    enemy->position.x = start_pos.x;
    enemy->position.y = start_pos.y;

    enemy->rect.width  = 45.0f;
    enemy->rect.height = 45.0f;

    enemy->rotation.angle = 0.0f;

    enemy->color.tint = GRAY;

    enemy->text.text      = TextFormat("%d", enemy->level);
    enemy->text.font_size = 20.0f;
    enemy->text.spacing   = 0.0f;
    enemy->text.tint      = WHITE;

    enemy->move.speed     = 100.0f;
    enemy->move.direction = (Vector2){0, 0};

    enemy->animation.max_hit_timer = 0.1f;
    enemy->animation.hit_timer     = 0.0f;
}

void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos) {
    assert(enemy);

    enemy->text.text = TextFormat("%d", enemy->level.current);

    system_set_direction(&enemy->position, &enemy->move, target_pos);
    system_move(&enemy->position, &enemy->move, dt);
    system_set_bounds(&enemy->position, &enemy->rect, (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(&enemy->animation, dt);
}

void enemy_draw(const Enemy* enemy) {
    assert(enemy);

    system_draw_rect(
        &enemy->position, &enemy->rect, &enemy->rotation, &enemy->color, &enemy->animation);
    system_draw_centered_text(
        &enemy->position, enemy->rect.width / 2.0f, enemy->rect.height / 2.0f, &enemy->text);
}
