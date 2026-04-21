#include "collision_manager.hpp"
#include "settings.hpp"
#include "systems.hpp"
#include <cmath>

enum class CollisionType {
    check,
    one_way,
    two_way,
};

// in one way collision: 1 is mobile and 2 is stationary
static bool aabb_collision(const CollisionType type,
                           PositionComponent &position1, const float half_w1,
                           const float half_h1, PositionComponent &position2,
                           const float half_w2, const float half_h2)
{
    // change in distance
    const float dx = position2.x - position1.x;
    const float dy = position2.y - position1.y;

    const float total_half_w = half_w1 + half_w2;
    const float total_half_h = half_h1 + half_h2;

    // penetration
    const float px = total_half_w - std::abs(dx);
    const float py = total_half_h - std::abs(dy);

    if (px > 0 && py > 0) {
        if (type == CollisionType::check)
            return true;

        if (px < py) {
            if (dx > 0) {
                if (type == CollisionType::one_way)
                    position1.x -= px;
                if (type == CollisionType::two_way) {
                    position1.x -= px / 2.0f;
                    position2.x += px / 2.0f;
                }
            } else {
                if (type == CollisionType::one_way)
                    position1.x += px;
                if (type == CollisionType::two_way) {
                    position1.x += px / 2.0f;
                    position2.x -= px / 2.0f;
                }
            }
        } else {
            if (dy > 0) {
                if (type == CollisionType::one_way)
                    position1.y -= py;
                if (type == CollisionType::two_way) {
                    position1.y -= py / 2.0f;
                    position2.y += py / 2.0f;
                }
            } else {
                if (type == CollisionType::one_way)
                    position1.y += py;
                if (type == CollisionType::two_way) {
                    position1.y += py / 2.0f;
                    position2.y -= py / 2.0f;
                }
            }
        }

        return true;
    }

    return false;
}

void player_colision_enemy(Player &player, EnemyManager &enemy_manager)
{
    int total_damage = 0;

    for (Enemy &enemy : enemy_manager.enemies) {
        if (aabb_collision(CollisionType::two_way, player.position,
                           player.rect.width / 2.0f, player.rect.height / 2.0f,
                           enemy.position, enemy.rect.width / 2.0f,
                           enemy.rect.height / 2.0f) &&
            player.animation.hit_timer <= 0) {
            //
            total_damage += enemy.damage.amount;
        }
    }

    if (total_damage > 0) {
        player.health.hp -= total_damage;
        player.animation.hit_timer = MAX_HIT_TIMER;
    }
}

void player_colision_drop(Player &player, DropManager &drop_manager)
{
    for (Drop &drop : drop_manager.drops) {
        if (aabb_collision(CollisionType::check, player.position,
                           player.rect.width / 2.0f, player.rect.height / 2.0f,
                           drop.position, drop.circle.radius,
                           drop.circle.radius)) {
            //
            system_add_xp(player.level, player.xp, drop.drop.amount);

            drop.state.active = false;
        }
    }
}

void bullet_colision_enemy(BulletManager &bullet_manager,
                           EnemyManager &enemy_manager)
{
    for (Bullet &bullet : bullet_manager.bullets) {
        for (Enemy &enemy : enemy_manager.enemies) {
            if (aabb_collision(CollisionType::check, enemy.position,
                               enemy.rect.width / 2.0f,
                               enemy.rect.height / 2.0f, bullet.position,
                               bullet.circle.radius, bullet.circle.radius) &&
                enemy.animation.hit_timer <= 0) {
                //
                enemy.health.hp -= bullet.damage.amount;
                enemy.animation.hit_timer = MAX_HIT_TIMER;

                bullet.lifetime.remaining = 0;
            }
        }
    }
}

void enemy_colision_enemy(EnemyManager &enemy_manager)
{
    for (size_t i = 0; i < enemy_manager.enemies.size(); i++) {
        Enemy &enemy1 = enemy_manager.enemies[i];

        for (size_t j = i + 1; j < enemy_manager.enemies.size(); j++) {
            Enemy &enemy2 = enemy_manager.enemies[j];

            aabb_collision(CollisionType::two_way, enemy1.position,
                           enemy1.rect.width / 2.0f, enemy1.rect.height / 2.0f,
                           enemy2.position, enemy2.rect.width / 2.0f,
                           enemy2.rect.height / 2.0f);
        }
    }
}
