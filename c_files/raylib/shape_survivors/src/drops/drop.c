#include "../systems.h"
#include "drop.h"
#include <assert.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

void drop_init(Drop* drop, const DropType type, const Vector2 start_pos) {
    assert(drop);
    drop->state.active = true;

    drop->position.x = start_pos.x;
    drop->position.y = start_pos.y;

    drop->circle.radius = 20.0f;

    drop->color.tint = ORANGE;

    drop->text.font_size = 20.0f;
    drop->text.spacing   = 2.0f;
    drop->text.tint      = WHITE;

    drop->type = type;

    switch (drop->type) {
        case DROP_TYPE_NONE:
            drop->state.active = false;
            return;
        case DROP_TYPE_XP:
            drop->text.string= "XP";
            drop->amount    = 20;
            break;
        case DROP_TYPE_HP:
            drop->text.string= "HP";
            drop->amount    = 10;
            break;
        default:
            printf("Unknown drop type: %d\n", type);
            exit(EXIT_FAILURE);
    }
}

void drop_draw(const Drop* drop) {
    assert(drop);

    system_draw_circle(&drop->position, &drop->circle, &drop->color);

    system_draw_centered_text(
        &drop->position, drop->circle.radius * 2, drop->circle.radius * 2, &drop->text);
}
