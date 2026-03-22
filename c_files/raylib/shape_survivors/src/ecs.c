#include "../include/ecs.h"

#include <assert.h>

uint32_t create_entity(World *world)
{
    assert(world);

    if (world->entity_count < MAX_ENTITIES) {
        return world->entity_count++;
    }

    return -1;
}

void delete_entity(World *world, const uint32_t id)
{
    assert(world);
    assert(id < world->entity_count);

    const uint32_t last_id = world->entity_count - 1;

    if (id < last_id) {
        world->mask_list[id]     = world->mask_list[last_id];
        world->position_list[id] = world->position_list[last_id];
        world->size_list[id]     = world->size_list[last_id];
        world->radius_list[id]   = world->radius_list[last_id];
        world->color_list[id]    = world->color_list[last_id];
        world->move_list[id]     = world->move_list[last_id];
        world->health_list[id]   = world->health_list[last_id];
        world->damage_list[id]   = world->damage_list[last_id];
        world->lifetime_list[id] = world->lifetime_list[last_id];
        world->target_list[id]   = world->target_list[last_id];
    }

    world->mask_list[last_id] = 0;
    world->entity_count--;
}
