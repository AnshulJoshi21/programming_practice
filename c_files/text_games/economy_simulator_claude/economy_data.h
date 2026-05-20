#pragma once
#include <stdint.h>
#include "config.h"

// ══════════════════════════════════════════════════════════════════════
//  GOODS  — what gets traded
// ══════════════════════════════════════════════════════════════════════
typedef struct {
    char     name[24];
    float    base_price;         // historical anchor price
    float    price;              // current market price
    float    supply;             // units available this tick
    float    demand;             // units demanded this tick
    float    traded_volume;      // units actually traded this tick
    float    price_history[52];  // ring buffer — last 52 ticks
    uint8_t  history_head;
    uint8_t  is_luxury;          // luxury goods have higher elasticity
} Good;

typedef struct {
    Good     items[MAX_GOODS];
    int      count;
} GoodStore;

// ══════════════════════════════════════════════════════════════════════
//  PRODUCERS  — make goods from inputs
// ══════════════════════════════════════════════════════════════════════
typedef struct {
    uint8_t  good_id;            // what they produce
    uint8_t  input_good_id;      // what they consume to produce (255 = none)
    uint8_t  market_id;          // which market they operate in
    uint8_t  alive;

    float    capital;            // money held
    float    efficiency;         // output per unit labor (improves with tech)
    float    output_last;        // units produced last tick
    float    labor_units;        // how much labor hired

    float    target_labor;       // desired labor (set by production system)
    float    profit_last;        // last tick profit (used for investment decisions)
    float    cumulative_profit;  // lifetime profit
    uint32_t ticks_alive;
} Producer;

typedef struct {
    Producer items[MAX_PRODUCERS];
    int      count;
} ProducerStore;

// ══════════════════════════════════════════════════════════════════════
//  CONSUMERS  — buy goods, have preferences
// ══════════════════════════════════════════════════════════════════════
typedef struct {
    uint8_t  market_id;
    uint8_t  alive;

    float    income;             // weekly income
    float    savings;            // accumulated savings
    float    utility;            // current satisfaction (0–1)

    // spending preferences per good (normalized weights)
    float    pref_weight[MAX_GOODS];

    // what was actually bought this tick
    float    bought[MAX_GOODS];
    float    spent_total;
    uint32_t ticks_alive;
} Consumer;

typedef struct {
    Consumer items[MAX_CONSUMERS];
    int      count;
} ConsumerStore;

// ══════════════════════════════════════════════════════════════════════
//  MARKETS  — regional trading hubs
// ══════════════════════════════════════════════════════════════════════
typedef struct {
    char     name[24];
    float    trade_tax;          // fraction of transaction value taken
    float    transport_cost;     // flat cost added to goods coming in
    float    total_gdp;          // sum of all transactions this tick
    float    gdp_history[52];
    uint8_t  gdp_head;
    uint32_t tick;
} Market;

typedef struct {
    Market   items[MAX_MARKETS];
    int      count;
} MarketStore;

// ══════════════════════════════════════════════════════════════════════
//  WORLD  — top-level simulation state (all in one struct for easy passing)
// ══════════════════════════════════════════════════════════════════════
typedef struct {
    GoodStore     goods;
    ProducerStore producers;
    ConsumerStore consumers;
    MarketStore   markets;

    uint32_t      tick;
    float         global_tech_level;    // grows over time, boosts efficiency
    float         total_money_supply;   // tracked for macro analysis
    float         inflation_index;      // cumulative inflation multiplier
} World;
