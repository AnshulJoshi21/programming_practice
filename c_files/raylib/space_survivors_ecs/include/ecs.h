#ifndef ECS_H
#define ECS_H

#include "components.h"
#include "settings.h"

typedef struct World
{
    int mask_list[MAX_ENTITIES];
    TransformComponent transform_list[MAX_ENTITIES];
    SpriteComponent sprite_list[MAX_ENTITIES];
    MoveComponent move_list[MAX_ENTITIES];
    HealthComponent health_list[MAX_ENTITIES];
    DamageComponent damage_list[MAX_ENTITIES];
    LifetimeComponent lifetime_list[MAX_ENTITIES];
    TargetComponent target_list[MAX_ENTITIES];

    int enttity_count;

} World;

int create_entity(World *world);
void delete_entity(World *world, const int id);

#endif // ECS_H
