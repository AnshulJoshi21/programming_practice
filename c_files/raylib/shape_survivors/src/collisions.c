#include "collisions.h"
#include "components.h"
#include "settings.h"
#include "systems.h"

#include <assert.h>
#include <math.h>

typedef enum CollisionType {
    COLLISION_CHECK,
    COLLISION_ONE_WAY,
    COLLISION_TWO_WAY

} CollisionType;

// in one way collision: 2 is stationary and 1 is mobile
static bool _aabb_collision(const CollisionType type, PositionComponent* pos1, const Vector2 size1,
                            PositionComponent* pos2, const Vector2 size2) {
    assert(pos1);
    assert(pos2);

    const float dx = pos2->x - pos1->x;
    const float dy = pos2->y - pos1->y;

    const float total_half_w = (size1.x + size2.x) / 2.0f;
    const float total_half_h = (size1.y + size2.y) / 2.0f;

    const float px = total_half_w - fabsf(dx);
    const float py = total_half_h - fabsf(dy);

    if (px > 0 && py > 0) {
        if (type == COLLISION_CHECK) {
            return true;
        }

        if (px < py) {
            const float half_px = px / 2.0f;
            if (dx > 0) {
                if (type == COLLISION_ONE_WAY) {
                    pos1->x -= px;
                } else if (type == COLLISION_TWO_WAY) {
                    pos1->x -= half_px;
                    pos2->x += half_px;
                }
            } else {
                if (type == COLLISION_ONE_WAY) {
                    pos1->x += px;
                } else if (type == COLLISION_TWO_WAY) {
                    pos1->x += half_px;
                    pos2->x -= half_px;
                }
            }

        } else {
            const float half_py = py / 2.0f;
            if (dy > 0) {
                if (type == COLLISION_ONE_WAY) {
                    pos1->y -= py;
                } else if (type == COLLISION_TWO_WAY) {
                    pos1->y -= half_py;
                    pos2->y += half_py;
                }
            } else {
                if (type == COLLISION_ONE_WAY) {
                    pos1->y += py;
                } else if (type == COLLISION_TWO_WAY) {
                    pos1->y += half_py;
                    pos2->y -= half_py;
                }
            }
        }

        return true;
    }

    return false;
}

void player_collision_enemies(Player* player, EnemyManager* em) {
    assert(player);
    assert(em);

    int total_damage = 0;

    for (int i = 0; i < em->spawner.count; i++) {
        Enemy* enemy = &em->enemies[i];

        if (_aabb_collision(COLLISION_TWO_WAY, &player->position,
                            (Vector2){player->rect.width, player->rect.height}, &enemy->position,
                            (Vector2){enemy->rect.width, enemy->rect.height}) &&
            player->animation.hit_timer <= 0) {
            //
            total_damage += enemy->damage.value;
        }
    }

    if (total_damage > 0) {
        player->health.hp -= total_damage;
        player->animation.hit_timer = MAX_HIT_TIMER;
    }
}

void bullet_collision_enemies(BulletManager* bm, EnemyManager* em, ParticleManager* pm) {
    assert(bm);
    assert(em);
    assert(pm);

    for (int i = 0; i < bm->spawner.count; i++) {
        Bullet* bullet = &bm->bullets[i];

        for (int j = 0; j < em->spawner.count; j++) {
            Enemy* enemy = &em->enemies[j];

            if (_aabb_collision(COLLISION_ONE_WAY, &bullet->position,
                                (Vector2){bullet->circle.radius, bullet->circle.radius},
                                &enemy->position,
                                (Vector2){enemy->rect.width, enemy->rect.height}) &&
                enemy->animation.hit_timer <= 0) {
                //
                enemy->health.hp -= bullet->damage.value;
                enemy->animation.hit_timer = MAX_HIT_TIMER;

                // particle effect
                particle_manager_spawn(pm, PARTICLE_SPARK,
                                       (Vector2){bullet->position.x, bullet->position.y});

                // despawn bullet
                bullet->lifetime.remaining = 0;
                break;
            }
        }
    }
}

void enemy_collision_enemies(EnemyManager* em) {
    assert(em);

    for (int i = 0; i < em->spawner.count; i++) {
        Enemy* enemy1 = &em->enemies[i];

        for (int j = i + 1; j < em->spawner.count; j++) {
            Enemy* enemy2 = &em->enemies[j];

            _aabb_collision(COLLISION_TWO_WAY, &enemy1->position,
                            (Vector2){enemy1->rect.width, enemy1->rect.height}, &enemy2->position,
                            (Vector2){enemy2->rect.width, enemy2->rect.height});
        }
    }
}

void player_collision_drops(Player* player, DropManager* dm) {
    assert(player);
    assert(dm);

    for (int i = 0; i < dm->spawner.count; i++) {
        Drop* drop = &dm->drops[i];

        if (_aabb_collision(COLLISION_CHECK, &player->position,
                            (Vector2){player->rect.width, player->rect.height}, &drop->position,
                            (Vector2){drop->circle.radius, drop->circle.radius})) {
            //
            system_add_xp(&player->xp, &drop->drop);

            // despawn drop
            drop->state.active = false;
            break;
        }
    }
}
