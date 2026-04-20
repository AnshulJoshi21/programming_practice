#include "enemy.h"

#include "../settings.h"
#include "../systems.h"
#include "../utils.h"

#include <assert.h>
#include <math.h>

static Color _get_random_color(void) {
    int random_num = GetRandomValue(1, 5);
    Color random_color;

    switch (random_num) {
        case 1:
            random_color = DARKBLUE;
            break;
        case 2:
            random_color = DARKBROWN;
            break;
        case 3:
            random_color = DARKGRAY;
            break;
        case 4:
            random_color = DARKGREEN;
            break;
        case 5:
            random_color = DARKPURPLE;
            break;
    }

    return random_color;
}

void enemy_init(Enemy *enemy, const EnemyType type, const Vector2 target_pos) {
    assert(enemy);

    const float random_angle = random_float(0, 2 * PI);
    const float random_distance = random_float(SCREEN_WIDTH + 100.0f, SCREEN_HEIGHT + 200.0f);
    const Vector2 start_pos = (Vector2){
        cosf(random_angle) * random_distance + target_pos.x,
        sinf(random_angle) * random_distance + target_pos.y,
    };

    enemy->type = type;

    enemy->position.x = start_pos.x;
    enemy->position.y = start_pos.y;

    enemy->rect.width = 45.0f;
    enemy->rect.height = 45.0f;

    enemy->rotation.value = 0.0f;

    enemy->color.tint = _get_random_color();

    enemy->text.text = "E";

    enemy->move.speed = 100.0f;
    enemy->move.direction = (Vector2){0, 0};

    enemy->health.max_hp = 5;
    enemy->health.hp = enemy->health.max_hp;

    enemy->damage.value = GetRandomValue(1, 3);

    enemy->animation.hit_timer = 0.0f;
}

void enemy_draw(const Enemy *enemy) {
    assert(enemy);

    system_draw_rect(&enemy->position, &enemy->rect, &enemy->rotation, &enemy->color, &enemy->text,
                     &enemy->animation);
}

void enemy_update(Enemy *enemy, const float dt, const Vector2 target_pos) {
    assert(enemy);

    system_set_direction(&enemy->position, &enemy->move, target_pos);
    system_move(&enemy->position, &enemy->move, dt);
    system_set_bounds_rect(&enemy->position, &enemy->rect, (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(&enemy->animation, dt);
}
