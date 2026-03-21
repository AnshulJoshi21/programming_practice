#ifndef ENTITIES_H
#define ENTITIES_H

#include "ecs.h"

int create_player(World *world);
int create_enemy(World *world, Vector2 target_pos);
int create_laser(World *world, const Vector2 start_pos, Vector2 target_pos);

#endif // ENTITIES_H
