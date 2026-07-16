#include "collision_manager.hpp"
#include <cmath>

static bool aabb(const CollisionType  type,
                 Components::Position pos1,
                 const float          half_w1,
                 const float          half_h1,
                 Components::Position pos2,
                 const float          half_w2,
                 const float          half_h2) {
    // distance
    const float dx = pos2.x - pos1.x;
    const float dy = pos2.y - pos1.y;

    // total half size
    const float total_half_w = half_w1 + half_w2;
    const float total_half_h = half_h1 + half_h2;

    // penetration
    const float px = total_half_w - std::fabs(dx);
    const float py = total_half_h - std::fabs(dy);

    if (px > 0 && py > 0) {
        if (type == CollisionType::CHECK)
            return true;

        if (px < py) {
            if (dx > 0) {
                if (type == CollisionType::ONE_WAY)
                    pos1.x -= px;
                else if (type == CollisionType::TWO_WAY) {
                    pos1.x -= px / 2.0f;
                    pos2.x += px / 2.0f;
                }
            } else {
                if (type == CollisionType::ONE_WAY)
                    pos1.x += px;
                else if (type == CollisionType::TWO_WAY) {
                    pos1.x += px / 2.0f;
                    pos2.x -= px / 2.0f;
                }
            }
        } else {
            if (dy > 0) {
                if (type == CollisionType::ONE_WAY)
                    pos1.y -= py;
                else if (type == CollisionType::TWO_WAY) {
                    pos1.y -= py / 2.0;
                    pos2.y += py / 2.0;
                }
            } else {
                if (type == CollisionType::ONE_WAY)
                    pos1.y += py;
                else if (type == CollisionType::TWO_WAY) {
                    pos1.y += py / 2.0f;
                    pos2.y -= py / 2.0f;
                }
            }
        }

        return true;
    }
    return false;
}

CollisionManager::CollisionManager(Player&        player,
                                   EnemyManager&  enemy_manager,
                                   BulletManager& bullet_manager,
                                   DropManager&   drop_manager)
    : player(player), enemy_manager(enemy_manager), bullet_manager(bullet_manager),
      drop_manager(drop_manager) {}

void CollisionManager::player_vs_enemy(void) {
    int total_damage = 0;

    for (Enemy& enemy : enemy_manager.enemies) {
        if (aabb(CollisionType::TWO_WAY,
                 player.position,
                 player.rect.width / 2.0f,
                 player.rect.height / 2.0f,
                 enemy.position,
                 enemy.rect.width / 2.0f,
                 enemy.rect.height / 2.0f)
            && player.animation.hit_timer <= 0)
            total_damage += enemy.damage.current;
    }

    if (total_damage > 0) {
        player.health.current -= total_damage;
        player.animation.hit_timer = player.animation.max_hit_timer;
    }
}

void CollisionManager::player_vs_drop(void) {
    for (Drop& drop : drop_manager.drops) {
        if (!drop.state.active)
            continue;

        if (aabb(CollisionType::CHECK,
                 player.position,
                 player.rect.width / 2.0f,
                 player.rect.height / 2.0f,
                 drop.position,
                 drop.circle.radius,
                 drop.circle.radius)) {
            // add drop value to player
            if (drop.type == DropType::HP)
                player.health.current += drop.amount;
            else if (drop.type == DropType::XP)
                player.xp.current += drop.amount;

            // despawn drop
            drop.state.active = false;
        }
    }
}

void CollisionManager::bullet_vs_enemy(void) {
    for (Bullet& bullet : bullet_manager.bullets) {
        for (Enemy& enemy : enemy_manager.enemies) {
            if (aabb(CollisionType::CHECK,
                     bullet.position,
                     bullet.circle.radius,
                     bullet.circle.radius,
                     enemy.position,
                     enemy.rect.width / 2.0f,
                     enemy.rect.height / 2.0f)
                && enemy.animation.hit_timer <= 0) {
                //
                enemy.health.current -= bullet.damage.current;
                enemy.animation.hit_timer = enemy.animation.max_hit_timer;

                bullet.lifetime.current = 0;
                break;
            }
        }
    }
}

void CollisionManager::enemy_vs_enemy(void) {
    const int enemies_size = static_cast<int>(enemy_manager.enemies.size());
    for (int i = 0; i < enemies_size; i++) {
        Enemy& enemy1 = enemy_manager.enemies[i];

        for (int j = i + 1; j < enemies_size; j++) {
            Enemy& enemy2 = enemy_manager.enemies[j];

            aabb(CollisionType::TWO_WAY,
                 enemy1.position,
                 enemy1.rect.width / 2.0f,
                 enemy1.rect.height / 2.0f,
                 enemy2.position,
                 enemy2.rect.width / 2.0f,
                 enemy2.rect.height / 2.0f);
        }
    }
}

void CollisionManager::update(void) {
    player_vs_enemy();
    player_vs_drop();
    bullet_vs_enemy();
    enemy_vs_enemy();
}
