#pragma once

#include <raylib.h>
#include <string>

namespace Components {

struct Level {
    int current;
    int pending;
};

struct Xp {
    int current;
    int next;
};

struct State {
    bool active;
};

struct Position {
    float x;
    float y;
};

struct Rect {
    float width;
    float height;
};

struct Circle {
    float radius;
};

struct Rotation {
    float angle;
};

struct Color_ {
    Color tint;
};

struct Text {
    std::string text;
    float       font_size;
    float       spacing;
    Color       tint;
};

struct Movement {
    float   speed;
    Vector2 direction;
};

struct Health {
    int max;
    int current;
};

struct Damage {
    int current;
};

struct Lifetime {
    float max;
    float current;
};

struct Animation {
    float max_hit_timer;
    float hit_timer;
};

struct Spawner {
    int max;
};

struct Timer {
    float elapsed;
    float interval;

    bool tick(void) {
        float current = GetTime();
        if (current - elapsed >= interval) {
            elapsed = current;
            return true;
        }

        return false;
    }
};

} // namespace Components
