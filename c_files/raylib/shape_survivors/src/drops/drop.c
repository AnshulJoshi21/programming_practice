#include "drop.h"

#include "../systems.h"

#include <assert.h>

void drop_init(Drop* drop, const DropType type, const Vector2 start_pos) {
    assert(drop);

    drop->position.x = start_pos.x;
    drop->position.y = start_pos.y;

    drop->state.active = true;

    drop->drop.type = type;
    switch (type) {
        case DROP_XP:
            drop->drop.amount = 10;

            drop->circle.radius = 10.0f;

            drop->color.tint = GOLD;
            break;
        case DROP_HEALTH:
            break;
        case DROP_MAX:
            break;
    }
}

void drop_draw(const Drop* drop) {
    assert(drop);

    if (!drop->state.active) {
        return;
    }

    system_draw_circle(&drop->position, &drop->circle, &drop->color);
}

// void drop_update(Drop* drop, const float dt) {
//     assert(drop);

//     // TODO: ADD PARTICLE EFFECTS OR ANYTHING ELSE REQUIRED
// }
