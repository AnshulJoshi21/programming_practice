#pragma once

#include <array>
#include <raylib.h>

enum class EnemyType {
    SCOUT = 0,
    GRUNT,
    TANK,
    CHARGER,
    BRUTE,
    MINI_BOSS,
    SWARM,
    SNIPER,
    COUNT,
};

struct EnemyDef {
    float width;
    float height;
    float damage;
    float hp;
    float speed;
    Color color;
};

constexpr std::array<EnemyDef, static_cast<std::size_t>(EnemyType::COUNT)> enemy_db = {{
    // SCOUT - Fast, fragile
    {20, 20, 5.0f, 20.0f, 300.0f, SKYBLUE},

    // GRUNT - Basic enemy
    {28, 28, 10.0f, 50.0f, 180.0f, GREEN},

    // TANK - Slow, durable
    {40, 40, 20.0f, 180.0f, 100.0f, DARKGREEN},

    // CHARGER - High speed, moderate HP
    {24, 24, 15.0f, 40.0f, 360.0f, ORANGE},

    // BRUTE - Heavy melee
    {48, 48, 30.0f, 250.0f, 80.0f, MAROON},

    // MINI_BOSS - Mid-game boss
    {64, 64, 40.0f, 600.0f, 120.0f, PURPLE},

    // SWARM - Tiny, weak, numerous
    {16, 16, 3.0f, 10.0f, 260.0f, YELLOW},

    // SNIPER - Keeps distance, frail
    {22, 22, 25.0f, 30.0f, 150.0f, RED},
}};
