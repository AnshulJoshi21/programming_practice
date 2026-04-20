#ifndef DROP_MANAGER_H
#define DROP_MANAGER_H

#include "drop.h"

#include "../components.h"

#define MAX_DROPS 100

typedef struct DropManager {
    Drop drops[MAX_DROPS];

    SpawnerComponent spawner;

} DropManager;

void drop_manager_init(DropManager* em);
void drop_manager_draw(const DropManager* em);
void drop_manager_update(DropManager* bm);

void drop_manager_spawn(DropManager* bm, const DropType type, const Vector2 start_pos);
void drop_manager_despawn(DropManager* bm, const int index);

#endif  // DROP_MANAGER_H
