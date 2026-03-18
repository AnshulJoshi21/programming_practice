#ifndef ECS_H
#define ECS_H

#include "components.h"
#include "settings.h"

typedef struct World
{
    int mask_list[MAX_ENTITIES];
    PositionComponent pos_list[MAX_ENTITIES];
    ColorComponent color_list[MAX_ENTITIES];
    MoveComponent move_list[MAX_ENTITIES];
    HealthComponent health_list[MAX_ENTITIES];
    DamageComponent damage_list[MAX_ENTITIES];
    AnimationComponent animation_list[MAX_ENTITIES];

    int entity_count;

} World;

int create_entity(World *world);
void delete_entity(World *world, const int id);

#endif // ECS_H
