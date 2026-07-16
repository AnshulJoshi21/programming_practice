#ifndef DROP_H
#define DROP_H

#include "../components.h"
#include <raylib.h>

typedef enum DropType {
    DROP_TYPE_NONE = 0,
    DROP_TYPE_XP,
    DROP_TYPE_HP,
    DROP_TYPE_MAX,
} DropType;

typedef struct Drop {
    CState    state;
    CPosition position;
    CCircle   circle;
    CColor    color;
    CText     text;
    DropType  type;
    int       amount;
} Drop;

void drop_init(Drop* drop, const DropType type, const Vector2 start_pos);
void drop_draw(const Drop* drop);

#endif // DROP_H
