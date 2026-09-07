#include "enemy_manager.h"
#include <assert.h>

void enemy_manager_init(EnemyManager* em) {
    assert(em);

    em->size  = 0;
    em->timer = (Timer){.elapsed = 0.0f, .duration = 3.0f};
}

void enemy_manager_spawn(EnemyManager* em, const float dt, const Vector2 target_pos) {
    assert(em);

    if (em->size >= MAX_ENEMIES) return;

    if (timer_tick(&em->timer, dt)) {
        enemy_init(&em->enemies[em->size], target_pos);
        em->size++;
    }
}

void enemy_manager_update(EnemyManager* em, const float dt, const Vector2 target_pos) {
    assert(em);

    enemy_manager_spawn(em, dt, target_pos);

    // update
    for (int i = 0; i < em->size; i++) {
        Enemy* enemy = &em->enemies[i];

        enemy_update(enemy, dt, target_pos);

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
