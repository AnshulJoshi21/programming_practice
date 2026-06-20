#pragma once

#include "drops/drop_type.h"
#include <raylib.h>

typedef struct {
    int current;
} LevelComponent;

typedef struct {
    int current;
    int next;
    int pending_levelups;
} XpComponent;

typedef struct {
    bool active;
} StateComponent;

typedef struct {
    float x;
    float y;
} PositionComponent;

typedef struct {
    float width;
    float height;
} RectComponent;

typedef struct {
    float radius;
} CircleComponent;

typedef struct {
    float angle;
} RotationComponent;

typedef struct {
    Color tint;
} ColorComponent;

typedef struct {
    const char* text;
    float       font_size;
    float       spacing;
    Color       tint;
} TextComponent;

typedef struct {
    float   speed;
    Vector2 direction;
} MoveComponent;

typedef struct {
    int max;
    int current;
} HealthComponent;

typedef struct {
    int value;
} DamageComponent;

typedef struct {
    float max;
    float remaining;
} LifetimeComponent;

typedef struct {
    float max_hit_timer;
    float hit_timer;
} AnimationComponent;

typedef struct {
    int max;
    int current;
} SpawnerComponent;

typedef struct {
    float elapsed;
    float interval;
} TimerComponent;

typedef struct {
    DropType type;
    int      amount;
} DropComponent;
