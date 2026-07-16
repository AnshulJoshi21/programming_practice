#ifndef DROP_MANAGER_H
#define DROP_MANAGER_H

#include "drop.h"

#define MAX_DROPS 200

typedef struct DropManager {
    Drop     drops[MAX_DROPS];
    CSpawner spawner;
} DropManager;

DropType drop_manager_get_random_drop_type(void);

void drop_manager_init(DropManager* dm);
void drop_manager_spawn(DropManager* dm, const DropType type, const Vector2 start_pos);
void drop_manager_despawn(DropManager* dm, const int index);
void drop_manager_update(DropManager* dm);
void drop_manager_draw(const DropManager* dm);

#endif // DROP_MANAGER_H
