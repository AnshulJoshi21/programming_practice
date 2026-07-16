#include "../systems.h"
#include "enemy_manager.h"
#include <assert.h>

void enemy_manager_init(EnemyManager* em) {
    assert(em);

    em->spawner.max     = MAX_ENEMIES;
    em->spawner.current = 0;

    em->timer.elapsed  = GetTime();
    em->timer.interval = 5.0f;
}

void enemy_manager_spawn(EnemyManager* em, const Vector2 target_pos) {
    assert(em);

    if (em->spawner.current >= em->spawner.max)
        return;

    if (em->spawner.current <= 0 || system_timer_tick(&em->timer)) {
        enemy_init(&em->enemies[em->spawner.current], target_pos);
        em->spawner.current++;
    }
}

void enemy_manager_despawn(EnemyManager* em, const int index) {
    assert(em);

    if (index < 0 || index >= em->spawner.current)
        return;

    em->enemies[index] = em->enemies[em->spawner.current - 1];
    em->spawner.current--;
}

void enemy_manager_update(EnemyManager* em,
                          const float   dt,
                          const Vector2 target_pos,
                          DropManager*  dm) {
    assert(em);
    assert(dm);

    enemy_manager_spawn(em, target_pos);

    for (int i = 0; i < em->spawner.current; i++) {
        Enemy* enemy = &em->enemies[i];

        enemy_update(enemy, dt, target_pos);

        if (enemy->health.current <= 0) {
            // spawn drop
            drop_manager_spawn(dm,
                               drop_manager_get_random_drop_type(),
                               (Vector2){enemy->position.x, enemy->position.y});

            enemy_manager_despawn(em, i);
            i--;
        }
    }
}

void enemy_manager_draw(const EnemyManager* em) {
    assert(em);

    for (int i = 0; i < em->spawner.current; i++) {
        enemy_draw(&em->enemies[i]);
    }
}
