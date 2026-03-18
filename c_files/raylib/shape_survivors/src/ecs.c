#include "../include/ecs.h"

#include <assert.h>

int create_entity(World *world)
{
    assert(world);

    if (world->entity_count < MAX_ENTITIES) {
        return world->entity_count++;
    }

    return -1;
}

void delete_entity(World *world, const int id)
{
    assert(world);
    assert(id < world->entity_count);

    const int last_id = world->entity_count - 1;

    // swap with last
    if (id != last_id) {
        world->mask_list[id]      = world->mask_list[last_id];
        world->pos_list[id]       = world->pos_list[last_id];
        world->color_list[id]     = world->color_list[last_id];
        world->move_list[id]      = world->move_list[last_id];
        world->health_list[id]    = world->health_list[last_id];
        world->damage_list[id]    = world->damage_list[last_id];
        world->animation_list[id] = world->animation_list[last_id];
    }

    // remove last
    world->entity_count--;
}
