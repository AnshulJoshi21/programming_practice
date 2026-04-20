#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "player.h"

#include "bullets/bullet_manager.h"
#include "drops/drop_manager.h"
#include "enemies/enemy_manager.h"
#include "particles/particle_manager.h"

void player_collision_enemies(Player* player, EnemyManager* em);
void bullet_collision_enemies(BulletManager* bm, EnemyManager* em, ParticleManager* pm);
void enemy_collision_enemies(EnemyManager* em);
void player_collision_drops(Player* player, DropManager* dm);

#endif  // COLLISIONS_H
