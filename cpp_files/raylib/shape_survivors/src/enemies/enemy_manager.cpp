#include "enemy_manager.hpp"

static const int ENEMIES_MAX = 200;

EnemyManager::EnemyManager()
    : spawner({.max = ENEMIES_MAX}),
      timer({.elapsed = static_cast<float>(GetTime()), .interval = 5.0f}) {}

void EnemyManager::spawn(const Vector2& target_pos) {
    const int enemies_size = static_cast<int>(enemies.size());

    if (enemies_size >= spawner.max)
        return;

    if (enemies_size <= 0 or timer.tick())
        enemies.push_back(Enemy(target_pos));
}

void EnemyManager::despawn(const int index) {
    const int enemies_size = static_cast<int>(enemies.size());

    if (index < 0 || index >= enemies_size)
        return;

    enemies[index] = enemies[enemies_size - 1];
    enemies.pop_back();
}

void EnemyManager::update(const float dt, const Vector2& target_pos, DropManager& drop_manager) {
    spawn(target_pos);

    for (int i = 0; i < static_cast<int>(enemies.size()); i++) {
        Enemy& enemy = enemies[i];

        enemy.update(dt, target_pos);

        if (enemy.health.current <= 0) {
            // spawn drop
            drop_manager.spawn(drop_manager.get_random_drop_type(),
                               {enemy.position.x, enemy.position.y});
            despawn(i);
            i--;
        }
    }
}

void EnemyManager::draw(void) const {
    for (const Enemy& enemy : enemies)
        enemy.draw();
}
