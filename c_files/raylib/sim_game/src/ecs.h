#pragma once

#include "components.h"

#define MAX_ENTITIES 10

typedef struct {
    int count;

    int id_to_index[MAX_ENTITIES];
    int index_to_id[MAX_ENTITIES];

    int       mask_list[MAX_ENTITIES];
    CState    state_list[MAX_ENTITIES];
    CPosition position_list[MAX_ENTITIES];
    CRect     rect_list[MAX_ENTITIES];
    CCircle   circle_list[MAX_ENTITIES];
    CRotation rotation_list[MAX_ENTITIES];
    CColor    color_list[MAX_ENTITIES];
    CText     text_list[MAX_ENTITIES];
    CMove     move_list[MAX_ENTITIES];
    CSpawner  spawner_list[MAX_ENTITIES];
    CTimer    timer_list[MAX_ENTITIES];

    int free_count;
    int free_list[MAX_ENTITIES];

} World;

void world_init(World* world);

int  world_create_entity(World* world);
void world_destroy_entity(World* world, const int id);

bool world_has_component(World* world, const int id, const int component);
void world_add_component(World* world, const int id, const int component);
void world_remove_component(World* world, const int id, const int component);
