#pragma once

struct Stats {
    int level;
};

struct Xp {
    float xp;
    float xp_next;
    int   pending_levelups;
};

struct Position {
    float x;
    float y;
    float z;
};

struct Size {
    float width;
    float height;
};

struct Health {
    float max;
    float current;
};

struct Damage {
    float value;
};

struct Target {
    float x;
    float y;
};

struct Timer {
    float elapsed;
    float interval;
};
