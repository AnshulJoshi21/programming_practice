#ifndef ECS_H
#define ECS_H

#include "components.h"
#include "settings.h"

#include <stdint.h>

typedef struct World
{
    uint32_t mask_list[MAX_ENTITIES];
    PositionComponent position_list[MAX_ENTITIES];
    SizeComponent size_list[MAX_ENTITIES];
    RadiusComponent radius_list[MAX_ENTITIES];
    ColorComponent color_list[MAX_ENTITIES];
    MoveComponent move_list[MAX_ENTITIES];
    HealthComponent health_list[MAX_ENTITIES];
    DamageComponent damage_list[MAX_ENTITIES];
    LifetimeComponent lifetime_list[MAX_ENTITIES];
    TargetComponent target_list[MAX_ENTITIES];

    uint32_t entity_count;

} World;

uint32_t create_entity(World *world);
void delete_entity(World *world, const uint32_t id);

#endif // ECS_H
