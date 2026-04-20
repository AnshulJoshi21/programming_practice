#ifndef DROP_H
#define DROP_H

#include "../components.h"

typedef enum DropType {
    DROP_XP = 0,
    DROP_HEALTH,
    DROP_MAX

} DropType;

typedef struct Drop {
    StateComponent state;
    PositionComponent position;
    CircleComponent circle;
    ColorComponent color;
    DropComponent drop;

} Drop;

void drop_init(Drop* drop, const DropType type, const Vector2 start_pos);
void drop_draw(const Drop* drop);
// void drop_update(Drop* drop, const float dt);

#endif  // DROP_H
