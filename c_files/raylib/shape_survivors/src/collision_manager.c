#include "collision_manager.h"
#include "components.h"
#include "systems.h"
#include <assert.h>
#include <math.h>

typedef enum CollisionType {
    COLLITION_TYPE_CHECK,
    COLLITION_TYPE_ONE_WAY,
    COLLITION_TYPE_TWO_WAY,
} CollisionType;

// in collision type one way, 1 is mobile and 2 is stationary
static bool aabb(const CollisionType type,
                 CPosition*          pos1,
                 const float         half_w1,
                 const float         half_h1,
                 CPosition*          pos2,
                 const float         half_w2,
                 const float         half_h2) {
    assert(pos1);
    assert(pos2);

    // distance
    const float dx = pos2->x - pos1->x;
    const float dy = pos2->y - pos1->y;

    const float total_half_w = half_w1 + half_w2;
    const float total_half_h = half_h1 + half_h2;

    // penetration
    const float px = total_half_w - fabsf(dx);
    const float py = total_half_h - fabsf(dy);

    if (px > 0 && py > 0) {
        if (type == COLLITION_TYPE_CHECK)
            return true;

        if (px < py) {
            if (dx > 0) {
                if (type == COLLITION_TYPE_ONE_WAY) {
                    pos1->x -= px;
                }
                if (type == COLLITION_TYPE_TWO_WAY) {
                    pos1->x -= px / 2.0f;
                    pos2->x += px / 2.0f;
                }
            } else {
                if (type == COLLITION_TYPE_ONE_WAY) {
                    pos1->x += px;
                }
                if (type == COLLITION_TYPE_TWO_WAY) {
                    pos1->x += px / 2.0f;
                    pos2->x -= px / 2.0f;
                }
            }
        } else {
            if (dy > 0) {
                if (type == COLLITION_TYPE_ONE_WAY) {
                    pos1->y -= py;
                }
                if (type == COLLITION_TYPE_TWO_WAY) {
                    pos1->y -= py / 2.0f;
                    pos2->y += py / 2.0f;
                }
            } else {
                if (type == COLLITION_TYPE_ONE_WAY) {
                    pos1->y += py;
                }
                if (type == COLLITION_TYPE_TWO_WAY) {
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

void collision_manager_player_vs_enemy(CollisionManager* cm) {
    assert(cm);

    int total_damage = 0;

    Player* player = cm->player;

    const int enemies_size = cm->enemy_manager->spawner.current;

    for (int i = 0; i < enemies_size; i++) {
        Enemy* enemy = &cm->enemy_manager->enemies[i];

        if (aabb(COLLITION_TYPE_TWO_WAY,
                 &player->position,
                 player->rect.width / 2.0f,
                 player->rect.height / 2.0f,
                 &enemy->position,
                 enemy->rect.width / 2.0f,
                 enemy->rect.height / 2.0f)
            && player->animation.hit_timer <= 0) {
            //
            total_damage += enemy->damage.amount;
        }
    }

    if (total_damage > 0) {
        player->animation.hit_timer = player->animation.hit_timer_max;
        player->health.current -= total_damage;
    }
}

void collision_manager_player_vs_drop(CollisionManager* cm) {
    assert(cm);

    Player* player = cm->player;

    const int drops_size = cm->drop_manager->spawner.current;

    for (int i = 0; i < drops_size; i++) {
        Drop* drop = &cm->drop_manager->drops[i];

        if (!drop->state.active)
            continue;

        if (aabb(COLLITION_TYPE_CHECK,
                 &player->position,
                 player->rect.width / 2.0f,
                 player->rect.height / 2.0f,
                 &drop->position,
                 drop->circle.radius,
                 drop->circle.radius)) {
            //
            if (drop->type == DROP_TYPE_XP)
                system_add_exp(&player->level, &player->exp, drop->amount);
            else if (drop->type == DROP_TYPE_HP)
                player->health.current += drop->amount;

            drop->state.active = false;
        }
    }
}

void collision_manager_bullet_vs_enemy(CollisionManager* cm) {
    assert(cm);
    const int bullets_size = cm->bullet_manager->spawner.current;
    const int enemies_size = cm->enemy_manager->spawner.current;

    for (int i = 0; i < bullets_size; i++) {
        Bullet* bullet = &cm->bullet_manager->bullets[i];

        for (int j = 0; j < enemies_size; j++) {
            Enemy* enemy = &cm->enemy_manager->enemies[j];

            if (aabb(COLLITION_TYPE_CHECK,
                     &bullet->position,
                     bullet->circle.radius,
                     bullet->circle.radius,
                     &enemy->position,
                     enemy->rect.width / 2.0f,
                     enemy->rect.height / 2.0f)
                && enemy->animation.hit_timer <= 0) {
                //
                enemy->animation.hit_timer = enemy->animation.hit_timer_max;
                enemy->health.current -= bullet->damage.amount;

                bullet->lifetime.remaining = 0;
                break;
            }
        }
    }
}

void collision_manager_enemy_vs_enemy(CollisionManager* cm) {
    assert(cm);

    const int enemies_size = cm->enemy_manager->spawner.current;

    for (int i = 0; i < enemies_size; i++) {
        Enemy* enemy1 = &cm->enemy_manager->enemies[i];

        for (int j = i + 1; j < enemies_size; j++) {
            Enemy* enemy2 = &cm->enemy_manager->enemies[j];

            aabb(COLLITION_TYPE_TWO_WAY,
                 &enemy1->position,
                 enemy1->rect.width / 2.0f,
                 enemy1->rect.height / 2.0f,
                 &enemy2->position,
                 enemy2->rect.width / 2.0f,
                 enemy2->rect.height / 2.0f);
        }
    }
}
