#include "ecs.h"

uint32_t create_player(World *world);
uint32_t create_enemy(World *world, const Vector2 *target_pos);
uint32_t create_bullet(World *world, const Vector2 start_pos,
                       const Vector2 *target_pos);
