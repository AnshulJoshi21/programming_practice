#pragma once

#include <raylib.h>

#define BIT(n) (1 << (n))

typedef enum {
    COMP_NONE     = 0,
    COMP_STATE    = BIT(2),
    COMP_POSITION = BIT(3),
    COMP_RECT     = BIT(4),
    COMP_CIRCLE   = BIT(5),
    COMP_Rotation = BIT(6),
    COMP_Color    = BIT(7),
    COMP_TEXT     = BIT(8),
    COMP_MOVE     = BIT(9),
    COMP_SPAWNER  = BIT(10),
    COMP_TIMER    = BIT(11),
} CMask;

typedef struct {
    bool active;
} CState;

typedef struct {
    float x;
    float y;
} CPosition;

typedef struct {
    float width;
    float height;
} CRect;

typedef struct {
    float radius;
} CCircle;

typedef struct {
    float angle;
} CRotation;

typedef struct {
    Color tint;
} CColor;

typedef struct {
    const char* text;
    float       font_size;
    float       spacing;
    Color       tint;
} CText;

typedef struct {
    float   speed;
    Vector2 direction;
} CMove;

typedef struct {
    int max;
    int current;
} CSpawner;

typedef struct {
    float elapsed;
    float interval;
} CTimer;
