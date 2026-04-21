#pragma once

#include "bullets/bullet_manager.hpp"
#include "drops/drop_manager.hpp"
#include "enemies/enemy_manager.hpp"
#include "player.hpp"

void player_colision_enemy(Player &player, EnemyManager &enemy_manager);
void player_colision_drop(Player &player, DropManager &drop_manager);
void bullet_colision_enemy(BulletManager &bullet_manager,
                           EnemyManager &enemy_manager);
void enemy_colision_enemy(EnemyManager &enemy_manager);
