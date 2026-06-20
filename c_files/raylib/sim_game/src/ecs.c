#include "ecs.h"
#include <assert.h>

void world_init(World* world) {
    assert(world);

    world->count      = 0;
    world->free_count = 0;

    for (int i = 0; i < MAX_ENTITIES; i++) {
        world->index_to_id[i] = -1;
        world->id_to_index[i] = -1;
        world->free_list[i]   = -1;
        world->mask_list[i]   = 0;
    }
}

int world_create_entity(World* world) {
    assert(world);

    if (world->count >= MAX_ENTITIES)
        return -1;

    if (world->free_count > 0) {
        int id = world->free_count;
        world->free_count--;

        return id;
    }

    int id                           = world->count;
    world->index_to_id[world->count] = id;
    world->count++;

    return id;
}

void world_destroy_entity(World* world, const int id) {
    assert(world);
    assert(id >= 0 && id < world->count);

    const int index = world->id_to_index[id];

    const int last_index = world->count - 1;
    const int last_id    = world->index_to_id[last_index];

    if (last_index > index) {
        world->mask_list[index]     = world->mask_list[last_index];
        world->state_list[index]    = world->state_list[last_index];
        world->position_list[index] = world->position_list[last_index];
        world->rect_list[index]     = world->rect_list[last_index];
        world->circle_list[index]   = world->circle_list[last_index];
        world->rotation_list[index] = world->rotation_list[last_index];
        world->color_list[index]    = world->color_list[last_index];
        world->text_list[index]     = world->text_list[last_index];
        world->move_list[index]     = world->move_list[last_index];
        world->spawner_list[index]  = world->spawner_list[last_index];
        world->timer_list[index]    = world->timer_list[last_index];

        world->index_to_id[index] = last_id;
    }

    world->free_list[world->free_count++] = id;
    world->count--;
}

bool world_has_component(World* world, const int id, const int component) {
    assert(world);
    assert(id >= 0 && id < world->count);

    return (world->mask_list[id] & component) == component;
}

void world_add_component(World* world, const int id, const int component) {
    assert(world);
    assert(id >= 0 && id < world->count);

    world->mask_list[id] |= component;
}

void world_remove_component(World* world, const int id, const int component) {
    assert(world);
    assert(id >= 0 && id < world->count);

    world->mask_list[id] &= ~component;
}
