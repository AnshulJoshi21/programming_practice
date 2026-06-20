#pragma once

#include "bullets/bullet_manager.h"
#include "drops/drop_manager.h"
#include "enemies/enemy_manager.h"
#include "player.h"

typedef enum {
    COLLISION_TYPE_CHECK,
    COLLISION_TYPE_ONE_WAY,
    COLLISION_TYPE_TWO_WAY,
} CollisionType;

typedef struct {
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
void collision_manager_update(CollisionManager* cm);
