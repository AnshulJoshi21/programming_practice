#include "drop_manager.h"
#include <assert.h>

void drop_manager_init(DropManager* dm) {
    assert(dm);
}

void drop_manager_spawn(DropManager* dm, const DropType type, const Vector2 start_pos) {
    assert(dm);

    drop_init(&dm->drops[dm->drops_size], type, start_pos);
    dm->drops_size++;
}

void drop_manager_despawn(DropManager* dm, const int index) {
    assert(dm);

    dm->drops[index] = dm->drops[dm->drops_size - 1];
    dm->drops_size--;
}

void drop_manager_update(DropManager* dm) {
    assert(dm);

    for (int i = 0; i < dm->drops_size; i++) {
        Drop* drop = &dm->drops[i];

        if (!drop->state.active) {
            drop_manager_despawn(dm, i);
            i--;
        }
    }
}

void drop_manager_draw(const DropManager* dm) {
    assert(dm);

    for (int i = 0; i < dm->drops_size; i++) {
        if (dm->drops[i].state.active)
            drop_draw(&dm->drops[i]);
    }
}
