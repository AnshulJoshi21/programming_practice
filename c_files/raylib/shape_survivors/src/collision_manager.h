#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "bullets/bullet_manager.h"
#include "drops/drop_manager.h"
#include "enemies/enemy_manager.h"
#include "player.h"

typedef struct CollisionManager {
    Player*        player;
    EnemyManager*  enemy_manager;
    BulletManager* bullet_manager;
    DropManager*   drop_manager;
} CollisionManager;

void collision_manager_init(CollisionManager* cm,
                            Player*           player,
                            EnemyManager*     enemy_manager,
                            BulletManager*    bullet_manager,
                            DropManager*      drop_manager);
void collision_manager_player_vs_enemy(CollisionManager* cm);
void collision_manager_player_vs_drop(CollisionManager* cm);
void collision_manager_bullet_vs_enemy(CollisionManager* cm);
void collision_manager_enemy_vs_enemy(CollisionManager* cm);

#endif // COLLISION_MANAGER_H
