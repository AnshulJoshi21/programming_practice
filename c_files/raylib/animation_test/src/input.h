#pragma once

#include <raylib.h>

typedef enum {
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_JUMP,
    ACTION_RUN,
    ACTION_ATTACK,

    ACTION_MAX

} Action;

typedef struct {
    KeyboardKey key;

} InputMap;

bool input_map_is_key_pressed(const InputMap *input_map, const Action action);
bool input_map_is_key_down(const InputMap *input_map, const Action action);
