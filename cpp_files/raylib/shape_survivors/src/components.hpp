#pragma once

#include "drops/drop_type.hpp"
#include <raylib.h>
#include <string>

struct LevelComponent {
    int current;
    int pending_levelups;
};

struct XpComponent {
    int xp;
    int xp_next;
};

struct StateComponent {
    bool active;
};

struct PositionComponent {
    float x;
    float y;
};

struct RectComponent {
    float width;
    float height;
};

struct CircleComponent {
    float radius;
};

struct RotationComponent {
    float angle;
};

struct ColorComponent {
    Color tint;
};

struct TextComponent {
    std::string text;
};

struct MoveComponent {
    float speed;
    Vector2 direction;
};

struct HealthComponent {
    int max_hp;
    int hp;
};

struct DamageComponent {
    int amount;
};

struct LifetimeComponent {
    float max;
    float remaining;
};

struct AnimationComponent {
    float hit_timer;
};

struct SpawnerComponent {
    size_t max;
};

struct TimerComponent {
    float elapsed;
    float interval;

    bool tick(void)
    {
        const float current = GetTime();
        if (current - elapsed >= interval) {
            elapsed = current;

            return true;
        }

        return false;
    }
};

struct DropComponent {
    DropType type;
    int amount;
};
