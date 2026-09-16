#include "enemy.h"
#include "enemy_manager.h"
#include <assert.h>

static const float ENEMY_SPAWN_INTERVAL = 3.0f;

void enemy_manager_init(EnemyManager* em) {
    assert(em);

    em->size = 0;
    interval_timer_init(&em->timer, ENEMY_SPAWN_INTERVAL);
}

void enemy_manager_spawn(EnemyManager* em, const float dt, const Player* player) {
    assert(em);

    if (em->size >= MAX_ENEMIES) return;

    if (em->size == 0 || interval_timer_tick(&em->timer, dt)) {
        const EnemyType random_type = GetRandomValue(0, ENEMY_TYPE_MAX - 1);
        enemy_init(&em->enemies[em->size++], random_type, player);
    }
}

void enemy_manager_update(EnemyManager* em, const float dt, const Player* player) {
    assert(em);

    enemy_manager_spawn(em, dt, player);

    for (int i = 0; i < em->size; i++) {
        Enemy* enemy = &em->enemies[i];

        enemy_update(enemy, dt);

        // despawn
        if (enemy->hp <= 0) {
            em->enemies[i] = em->enemies[--em->size];
            i--;
        }
    }
}

void enemy_manager_draw(const EnemyManager* em) {
    assert(em);

    for (int i = 0; i < em->size; i++) {
        enemy_draw(&em->enemies[i]);
    }
}
