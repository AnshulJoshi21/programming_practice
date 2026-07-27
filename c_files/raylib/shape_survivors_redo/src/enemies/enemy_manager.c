#include "enemy_manager.h"
#include <assert.h>

void enemy_manager_init(EnemyManager* em) {
    assert(em);

    em->enemies_max  = MAX_ENEMIES;
    em->enemies_size = 0;

    timer_interval_init(&em->timer, ENEMY_SPAWN_INTERVAL);
}

void enemy_manager_spawn(EnemyManager* em, const Vector2 target_pos) {
    assert(em);

    if (em->enemies_size >= em->enemies_max)
        return;

    if (em->enemies_size <= 0 || timer_interval_tick(&em->timer)) {
        const EnemyType random_enemy_type = (EnemyType) GetRandomValue(0, ENEMY_TYPE_MAX - 1);
        enemy_init(&em->enemies[em->enemies_size], random_enemy_type, target_pos);
        em->enemies_size++;
    }
}

void enemy_manager_despawn(EnemyManager* em, const int index) {
    assert(em);
    assert(index >= 0 && index < em->enemies_size);

    em->enemies[index] = em->enemies[em->enemies_size - 1];
    em->enemies_size--;
}

void enemy_manager_update(EnemyManager* em, const float dt, const Vector2 target_pos) {
    assert(em);

    enemy_manager_spawn(em, target_pos);

    for (int i = 0; i < em->enemies_size; i++) {
        Enemy* enemy = &em->enemies[i];

        enemy_update(enemy, dt, target_pos);

        if (enemy->hp <= 0) {
            enemy_manager_despawn(em, i);
            i--;
        }
    }
}

void enemy_manager_draw(const EnemyManager* em) {
    assert(em);

    for (int i = 0; i < em->enemies_size; i++) {
        enemy_draw(&em->enemies[i]);
    }
}
