#include "enemy_manager.hpp"

static const float ENEMY_SPAWN_INTERVAL = 2.0f;

EnemyManager::EnemyManager(void) : timer({.interval = ENEMY_SPAWN_INTERVAL}) {}

void EnemyManager::spawn(const Vector2& target_pos) {
    if (enemies.size() <= 0 || timer.tick()) {
        std::size_t random_enemy_type
            = GetRandomValue(0, (static_cast<std::size_t>(EnemyType::COUNT) - 1));

        enemies.push_back(Enemy(static_cast<EnemyType>(random_enemy_type), target_pos));
    }
}

void EnemyManager::despawn(const std::size_t index) {
    if (index >= enemies.size())
        return;

    enemies[index] = enemies.back();
    enemies.pop_back();
}

void EnemyManager::update(const float dt, const Vector2& target_pos) {
    spawn(target_pos);

    for (std::size_t i = 0; i < enemies.size(); i++) {
        Enemy& enemy = enemies[i];

        enemy.update(dt, target_pos);

        if (enemy.hp <= 0) {
            despawn(i);
            i--;
        }
    }
}

void EnemyManager::draw(void) const {
    for (const Enemy& enemy : enemies) {
        enemy.draw();
    }
}
