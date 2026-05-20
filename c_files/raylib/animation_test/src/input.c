#include "input.h"

bool input_map_is_key_pressed(const InputMap *input_map, const Action action)
{
    if (IsKeyPressed(input_map[action].key)) {
        return true;
    }

    return false;
}

bool input_map_is_key_down(const InputMap *input_map, const Action action)
{
    if (IsKeyDown(input_map[action].key)) {
        return true;
    }

    return false;
}
