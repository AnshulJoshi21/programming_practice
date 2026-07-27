#include "../utils.h"
#include "drop_manager.h"
#include <assert.h>

DropType drop_manager_get_random_drop_type(void) {
    const float random_chance = utils_randf(0.0f, 100.0f);

    if (random_chance >= 90.0f)
        return DROP_TYPE_HP;
    else if (random_chance >= 75.0f)
        return DROP_TYPE_XP;
    else
        return DROP_TYPE_XP;
}

void drop_manager_init(DropManager* dm) {
    assert(dm);

    dm->spawner.max     = MAX_DROPS;
    dm->spawner.current = 0;
}

void drop_manager_spawn(DropManager* dm, const DropType type, const Vector2 start_pos) {
    assert(dm);

    if (dm->spawner.current >= dm->spawner.max)
        return;

    drop_init(&dm->drops[dm->spawner.current], type, start_pos);
    dm->spawner.current++;
}

void drop_manager_despawn(DropManager* dm, const int index) {
    assert(dm);

    if (index < 0 || index >= dm->spawner.current)
        return;

    dm->drops[index] = dm->drops[dm->spawner.current - 1];
    dm->spawner.current--;
}

void drop_manager_update(DropManager* dm) {
    assert(dm);

    for (int i = 0; i < dm->spawner.current; i++) {
        Drop* drop = &dm->drops[i];

        if (!drop->state.active) {
            drop_manager_despawn(dm, i);
            i--;
        }
    }
}

void drop_manager_draw(const DropManager* dm) {
    assert(dm);

    for (int i = 0; i < dm->spawner.current; i++) {
        const Drop* drop = &dm->drops[i];

        if (!drop->state.active)
            continue;

        drop_draw(drop);
    }
}
