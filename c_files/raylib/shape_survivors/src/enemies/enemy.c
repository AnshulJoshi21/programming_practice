#include "../settings.h"
#include "../utils.h"
#include "enemy.h"
#include <assert.h>
#include <raymath.h>

void enemy_init(Enemy* enemy, const EnemyType type, const Player* player) {
    assert(enemy);

    enemy->player = player;

    const EnemyData* config = &enemy_db[type];

    const float random_angle = randf(0, 2 * PI);
    const float random_distance
        = randf(GetScreenWidth() / 2.0f + 100.0f, GetScreenWidth() / 2.0f + 200.0f);
    const Vector2 start_pos = (Vector2){
        cosf(random_angle) * random_distance + player->rect.x,
        sinf(random_angle) * random_distance + player->rect.y,
    };

    const Vector2 size = config->size;
    enemy->rect        = (Rectangle){start_pos.x, start_pos.y, size.x, size.y};
    enemy->origin      = (Vector2){enemy->rect.width / 2.0f, enemy->rect.height / 2.0f};
    enemy->rotation    = 0.0f;
    enemy->color       = palette.purple;

    enemy->speed     = config->speed;
    enemy->direction = (Vector2){0, 0};

    enemy->damage = config->damage;
    enemy->max_hp = config->hp;
    enemy->hp     = enemy->max_hp;

    enemy->max_hit_timer = 0.1f;
    enemy->hit_timer     = 0.0f;
}

void enemy_update(Enemy* enemy, const float dt) {
    assert(enemy);

    const Player* player   = enemy->player;
    const float   dx       = player->rect.x - enemy->rect.x;
    const float   dy       = player->rect.y - enemy->rect.y;
    const float   distance = sqrtf((dx * dx) + (dy * dy));
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
}
