#include "../systems.h"
#include "enemy_manager.h"
#include <assert.h>

void enemy_manager_init(EnemyManager* em) {
    assert(em);

    em->dead_enemy_count = 0;

    em->spawner = (SpawnerComponent){.max = 200, .current = 0};
    em->timer   = (TimerComponent){.elapsed = GetTime(), .interval = 1.0f};
}

void enemy_manager_spawn(EnemyManager* em, const int current_wave, const Vector2 target_pos) {
    assert(em);

    if (em->spawner.current >= em->spawner.max)
        return;

    if (em->spawner.current <= 0 || system_timer_tick(&em->timer)) {
        enemy_init(&em->enemies[em->spawner.current], current_wave, target_pos);
        em->spawner.current++;
    }
}

void enemy_manager_despawn(EnemyManager* em, const int index) {
    assert(em);

    em->enemies[index] = em->enemies[em->spawner.current - 1];
    em->spawner.current--;
}

void enemy_manager_update(EnemyManager* em,
                          const float   dt,
                          const int     current_wave,
                          const Vector2 target_pos,
                          DropManager*  dm) {
    assert(em);
    assert(dm);

    enemy_manager_spawn(em, current_wave, target_pos);

    for (int i = 0; i < em->spawner.current; i++) {
        Enemy* enemy = &em->enemies[i];

        enemy_update(enemy, dt, target_pos);

        if (enemy->level.current <= 0) {
            drop_manager_spawn(dm,
                               (DropType) GetRandomValue(DROP_TYPE_XP, DROP_TYPE_HP),
                               (Vector2){enemy->position.x, enemy->position.y});

            enemy_manager_despawn(em, i);
            i--;

            em->dead_enemy_count++;
        }
    }
}

void enemy_manager_draw(const EnemyManager* em) {
    assert(em);

    for (int i = 0; i < em->spawner.current; i++) {
        enemy_draw(&em->enemies[i]);
    }
}
