#include "collision_manager.h"
#include "components.h"
#include "systems.h"
#include <assert.h>
#include <math.h>

// NOTE: in one_way collision, 1 is mobile and 2 is stationary
static bool aabb_collision(const CollisionType type,
                           PositionComponent*  pos1,
                           const float         half_w1,
                           const float         half_h1,
                           PositionComponent*  pos2,
                           const float         half_w2,
                           const float         half_h2) {
    assert(pos1);
    assert(pos2);

    // delta distance
    const float dx = pos2->x - pos1->x;
    const float dy = pos2->y - pos1->y;

    // total distance
    const float total_half_w = half_w1 + half_w2;
    const float total_half_h = half_h1 + half_h2;

    // penetration
    const float px = total_half_w - fabsf(dx);
    const float py = total_half_h - fabsf(dy);

    if (px > 0 && py > 0) {
        if (type == COLLISION_TYPE_CHECK)
            return true;

        if (px < py) {
            if (dx > 0) {
                if (type == COLLISION_TYPE_ONE_WAY) {
                    pos1->x -= px;
                }
                if (type == COLLISION_TYPE_TWO_WAY) {
                    pos1->x -= px / 2.0f;
                    pos2->x += px / 2.0f;
                }
            } else {
                if (type == COLLISION_TYPE_ONE_WAY) {
                    pos1->x += px;
                }
                if (type == COLLISION_TYPE_TWO_WAY) {
                    pos1->x += px / 2.0f;
                    pos2->x -= px / 2.0f;
                }
            }
        } else {
            if (dy > 0) {
                if (type == COLLISION_TYPE_ONE_WAY) {
                    pos1->y -= py;
                }
                if (type == COLLISION_TYPE_TWO_WAY) {
                    pos1->y -= py / 2.0f;
                    pos2->y += py / 2.0f;
                }
            } else {
                if (type == COLLISION_TYPE_ONE_WAY) {
                    pos1->y += py;
                }
                if (type == COLLISION_TYPE_TWO_WAY) {
                    pos1->y += py / 2.0f;
                    pos2->y -= py / 2.0f;
                }
            }
        }

        return true;
    }

    return false;
}

void collision_manager_init(CollisionManager* cm,
                            Player*           player,
                            EnemyManager*     enemy_manager,
                            BulletManager*    bullet_manager,
                            DropManager*      drop_manager) {
    assert(cm);

    cm->player         = player;
    cm->enemy_manager  = enemy_manager;
    cm->bullet_manager = bullet_manager;
    cm->drop_manager   = drop_manager;
}

static void player_vs_enemy(CollisionManager* cm) {
    assert(cm);

    int total_damage = 0;

    for (int i = 0; i < cm->enemy_manager->spawner.current; i++) {
        Enemy* enemy = &cm->enemy_manager->enemies[i];

        if (aabb_collision(COLLISION_TYPE_TWO_WAY,
                           &cm->player->position,
                           cm->player->rect.width / 2.0f,
                           cm->player->rect.height / 2.0f,
                           &enemy->position,
                           enemy->rect.width / 2.0f,
                           enemy->rect.height / 2.0f)
            && cm->player->animation.hit_timer <= 0) {
            //
            total_damage += enemy->level.current;
        }
    }

    if (total_damage > 0) {
        cm->player->health.current -= total_damage;
        cm->player->animation.hit_timer = cm->player->animation.max_hit_timer;
    }
}

static void player_vs_drop(CollisionManager* cm) {
    assert(cm);

    for (int i = 0; i < cm->drop_manager->drops_size; i++) {
        Drop* drop = &cm->drop_manager->drops[i];

        if (!drop->state.active)
            continue;

        if (aabb_collision(COLLISION_TYPE_CHECK,
                           &cm->player->position,
                           cm->player->rect.width / 2.0f,
                           cm->player->rect.height / 2.0f,
                           &drop->position,
                           drop->circle.radius,
                           drop->circle.radius)) {
            //
            if (drop->drop.type == DROP_TYPE_XP)
                system_add_xp(&cm->player->level, &cm->player->xp, drop->drop.amount);
            if (drop->drop.type == DROP_TYPE_HP)
                cm->player->health.current += drop->drop.amount;

            drop->state.active = false;
            i--;
        }
    }
}

static void bullet_vs_enemy(CollisionManager* cm) {
    assert(cm);

    for (int i = 0; i < cm->bullet_manager->spawner.current; i++) {
        Bullet* bullet = &cm->bullet_manager->bullets[i];

        for (int j = 0; j < cm->enemy_manager->spawner.current; j++) {
            Enemy* enemy = &cm->enemy_manager->enemies[j];

            if (aabb_collision(COLLISION_TYPE_CHECK,
                               &bullet->position,
                               bullet->circle.radius,
                               bullet->circle.radius,
                               &enemy->position,
                               enemy->rect.width / 2.0f,
                               enemy->rect.height / 2.0f)
                && enemy->animation.hit_timer <= 0) {
                //
                enemy->level.current -= bullet->damage.value;
                enemy->animation.hit_timer = enemy->animation.max_hit_timer;

                bullet->lifetime.remaining = 0;
                i--;
                break;
            }
        }
    }
}

static void enemy_vs_enemy(CollisionManager* cm) {
    assert(cm);

    for (int i = 0; i < cm->bullet_manager->spawner.current; i++) {
        Enemy* enemy1 = &cm->enemy_manager->enemies[i];

        for (int j = i + 1; j < cm->enemy_manager->spawner.current; j++) {
            Enemy* enemy2 = &cm->enemy_manager->enemies[j];

            aabb_collision(COLLISION_TYPE_TWO_WAY,
                           &enemy1->position,
                           enemy1->rect.width / 2.0f,
                           enemy1->rect.height / 2.0f,
                           &enemy2->position,
                           enemy2->rect.width / 2.0f,
                           enemy2->rect.height / 2.0f);
        }
    }
}

void collision_manager_update(CollisionManager* cm) {
    assert(cm);
    player_vs_enemy(cm);
    player_vs_drop(cm);
    bullet_vs_enemy(cm);
    enemy_vs_enemy(cm);
}
