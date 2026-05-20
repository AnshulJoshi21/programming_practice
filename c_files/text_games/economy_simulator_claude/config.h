#pragma once

// ── Simulation Limits ──────────────────────────────────────────────
#define MAX_GOODS        16
#define MAX_PRODUCERS    256
#define MAX_CONSUMERS    512
#define MAX_MARKETS      8
#define MAX_AGENTS       768   // producers + consumers share agent pool

// ── Tick / Time ────────────────────────────────────────────────────
#define TICKS_PER_YEAR   52    // weekly ticks
#define DT               1.0f  // 1 tick = 1 week

// ── Economy Tuning ─────────────────────────────────────────────────
#define BASE_PRICE_ELASTICITY   0.15f   // price reacts to supply/demand ratio
#define PRICE_FLOOR             0.01f
#define PRICE_CEIL              9999.0f
#define CONSUMER_INCOME_BASE    100.0f
#define PRODUCER_CAPITAL_BASE   500.0f
#define WAGE_RATE               20.0f   // cost per unit of labor
#define INFLATION_RATE          0.001f  // per tick base inflation
#define TECH_GROWTH_RATE        0.0005f // efficiency improves over time

// ── Display ────────────────────────────────────────────────────────
#define DISPLAY_TICKS    4     // print every N ticks
#define SIM_TICKS        260   // 5 simulated years
