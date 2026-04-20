#include "enemy_manager.h"

#include "../systems.h"

#include <assert.h>

void enemy_manager_init(EnemyManager* em) {
    assert(em);

    em->spawner.max = MAX_ENEMIES;
    em->spawner.count = 0;

    em->timer.elapsed = GetTime();
    em->timer.interval = 3.0f;
}

void enemy_manager_draw(const EnemyManager* em) {
    assert(em);

    for (int i = 0; i < em->spawner.count; i++) {
        enemy_draw(&em->enemies[i]);
    }
}

void enemy_manager_spawn(EnemyManager* em, const EnemyType type, const Vector2 target_pos) {
    assert(em);

    if (em->spawner.count >= em->spawner.max) {
        return;
    }

    if (em->spawner.count <= 0 || system_timer_tick(&em->timer)) {
        enemy_init(&em->enemies[em->spawner.count], type, target_pos);
        em->spawner.count++;
    }
}

void enemy_manager_despawn(EnemyManager* em, const int index) {
    assert(em);
    assert(index >= 0 && index < em->spawner.count);

    em->enemies[index] = em->enemies[em->spawner.count - 1];
    em->spawner.count--;
}

void enemy_manager_update(EnemyManager* em, DropManager* dm, const float dt,
                          const Vector2 target_pos) {
    assert(em);

    enemy_manager_spawn(em, ENEMY_BASIC, target_pos);

    // update
    for (int i = 0; i < em->spawner.count; i++) {
        Enemy* enemy = &em->enemies[i];

        enemy_update(enemy, dt, target_pos);

        if (enemy->health.hp <= 0) {
            drop_manager_spawn(dm, DROP_XP, (Vector2){enemy->position.x, enemy->position.y});
            enemy_manager_despawn(em, i);
            i--;
        }
    }
}
