#pragma once

#include "../components.h"
#include "drop.h"

#define MAX_DROPS 1000

typedef struct {
    Drop drops[MAX_DROPS];
    int  drops_size;
} DropManager;

void drop_manager_init(DropManager* em);
void drop_manager_spawn(DropManager* em, const DropType type, const Vector2 start_pos);
void drop_manager_despawn(DropManager* em, const int index);
void drop_manager_update(DropManager* em);
void drop_manager_draw(const DropManager* em);
