#include "../include/ecs.h"

#include <assert.h>

int create_entity(World *world)
{
    assert(world);

    if (world->enttity_count < MAX_ENTITIES) {
        return world->enttity_count++;
    }

    return -1;
}

void delete_entity(World *world, const int id)
{
    assert(world);
    assert(id >= 0 && id < world->enttity_count);

    const int last_id = world->enttity_count - 1;

    // swap with last entity
    if (id < last_id) {
        world->mask_list[id]      = world->mask_list[last_id];
        world->transform_list[id] = world->transform_list[last_id];
        world->sprite_list[id]    = world->sprite_list[last_id];
        world->move_list[id]      = world->move_list[last_id];
        world->health_list[id]    = world->health_list[last_id];
        world->damage_list[id]    = world->damage_list[last_id];
        world->lifetime_list[id]  = world->lifetime_list[last_id];
        world->target_list[id]    = world->target_list[last_id];
    }

    // reset last entity
    world->mask_list[last_id]      = (int){0};
    world->transform_list[last_id] = (TransformComponent){0};
    world->sprite_list[last_id]    = (SpriteComponent){0};
    world->move_list[last_id]      = (MoveComponent){0};
    world->health_list[last_id]    = (HealthComponent){0};
    world->damage_list[last_id]    = (DamageComponent){0};
    world->lifetime_list[last_id]  = (LifetimeComponent){0};
    world->target_list[last_id]    = (TargetComponent){0};

    // resize
    world->enttity_count--;
}
