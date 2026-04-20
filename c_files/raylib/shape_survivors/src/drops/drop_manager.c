#include "drop_manager.h"

#include <assert.h>

void drop_manager_init(DropManager* dm) {
    assert(dm);

    dm->spawner.max = MAX_DROPS;
    dm->spawner.count = 0;
}

void drop_manager_draw(const DropManager* dm) {
    assert(dm);

    for (int i = 0; i < dm->spawner.count; i++) {
        drop_draw(&dm->drops[i]);
    }
}

void drop_manager_spawn(DropManager* dm, const DropType type, const Vector2 start_pos) {
    assert(dm);

    if (dm->spawner.count >= dm->spawner.max) {
        return;
    }

    drop_init(&dm->drops[dm->spawner.count], type, start_pos);
    dm->spawner.count++;
}

void drop_manager_despawn(DropManager* dm, const int index) {
    assert(dm);
    assert(index >= 0 && index < dm->spawner.count);

    dm->drops[index] = dm->drops[dm->spawner.count - 1];
    dm->spawner.count--;
}

void drop_manager_update(DropManager* dm) {
    assert(dm);

    // update
    for (int i = 0; i < dm->spawner.count; i++) {
        Drop* drop = &dm->drops[i];

        if (!drop->state.active) {
            drop_manager_despawn(dm, i);
            i--;
        }
    }
}
