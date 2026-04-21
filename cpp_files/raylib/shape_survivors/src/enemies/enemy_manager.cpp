#include "enemy_manager.hpp"

EnemyManager::EnemyManager()
    : spawner({.max = 200}),
      timer({.elapsed = static_cast<float>(GetTime()), .interval = 1.0f})
{
}

void EnemyManager::draw(void) const
{
    for (const Enemy &enemy : enemies) {
        enemy.draw();
    }
}

void EnemyManager::spawn(const Vector2 target_pos)
{
    if (enemies.size() >= spawner.max)
        return;

    if (enemies.size() <= 0 || timer.tick()) {
        enemies.push_back(Enemy({target_pos}));
    }
}

void EnemyManager::despawn(const size_t index)
{
    if (index >= enemies.size())
        return;

    enemies[index] = enemies.back();
    enemies.pop_back();
}

void EnemyManager::update(
    const float dt, const Vector2 target_pos,
    std::function<void(const DropType type, const Vector2 start_pos)>
        spawn_drop)
{
    spawn(target_pos);

    // update
    for (size_t i = 0; i < enemies.size(); i++) {
        Enemy &enemy = enemies[i];

        enemy.update(dt, target_pos);

        if (enemy.health.hp <= 0) {
            spawn_drop(DropType::xp, {enemy.position.x, enemy.position.y});
            despawn(i);
        }
    }
}
