#include "../settings.h"
#include "../utils.h"
#include "enemy.h"
#include <assert.h>
#include <raymath.h>

void enemy_init(Enemy* enemy, const EnemyType type, const Vector2 target_pos) {
    assert(enemy);

    enemy->type = type;

    const float random_angle    = utils_randf(0, 2 * PI);
    const float half_w          = GetScreenWidth() / 2.0f;
    const float random_distance = utils_randf(half_w, half_w + 100);

    enemy->pos = (Vector2){
        cosf(random_angle) * random_distance + target_pos.x,
        sinf(random_angle) * random_distance + target_pos.y,
    };

    const EnemyDef* def = &enemy_db[enemy->type];
    enemy->direction    = (Vector2){0, 0};
    enemy->hp           = def->hp;
    enemy->hit_timer    = 0.0f;
}

void enemy_update(Enemy* enemy, const float dt, const Vector2 target_pos) {
    assert(enemy);
    const EnemyDef* def = &enemy_db[enemy->type];

    // set direction
    const float dx       = target_pos.x - enemy->pos.x;
    const float dy       = target_pos.y - enemy->pos.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) {
        enemy->direction = (Vector2){dx / distance, dy / distance};

        // move
        enemy->pos.x += enemy->direction.x * def->speed * dt;
        enemy->pos.y += enemy->direction.y * def->speed * dt;

        // bounds
        enemy->pos.x = Clamp(enemy->pos.x, def->size.x / 2.0f, MAP_SIZE - def->size.x / 2.0f);
        enemy->pos.y = Clamp(enemy->pos.y, def->size.y / 2.0f, MAP_SIZE - def->size.y / 2.0f);
    }
}

void enemy_draw(const Enemy* enemy) {
    assert(enemy);
    const EnemyDef* def = &enemy_db[enemy->type];

    const Rectangle rect   = (Rectangle){enemy->pos.x, enemy->pos.y, def->size.x, def->size.y};
    const Vector2   origin = (Vector2){def->size.x / 2.0f, def->size.y / 2.0f};
    DrawRectanglePro(rect, origin, 0.0f, def->color);
}
