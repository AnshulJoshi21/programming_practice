#include "world_init.h"
#include "config.h"
#include <string.h>
#include <math.h>

// Simple deterministic pseudo-random (no stdlib rand dependency for reproducibility)
static uint32_t lcg_state = 12345;
static float lcg_randf(void) {
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return (float)(lcg_state >> 8) / (float)(1 << 24);
}

// ── Goods ─────────────────────────────────────────────────────────────
static void init_goods(GoodStore *gs) {
    // 6 goods: grain, iron, cloth, tools, food, luxury_goods
    // (input chain: grain→food, iron→tools, cloth→luxury_goods)
    const char *names[]       = {"Grain","Iron","Cloth","Food","Tools","Luxuries"};
    float       base_prices[] = {  5.0f,  12.0f,  8.0f,  15.0f, 30.0f,   80.0f };
    uint8_t     is_luxury[]   = {    0,     0,     0,      0,     0,       1    };

    gs->count = 6;
    for (int g = 0; g < gs->count; g++) {
        Good *good = &gs->items[g];
        memset(good, 0, sizeof(Good));
        strncpy(good->name, names[g], 23);
        good->base_price = base_prices[g];
        good->price      = base_prices[g];
        good->is_luxury  = is_luxury[g];
    }
}

// ── Markets ───────────────────────────────────────────────────────────
static void init_markets(MarketStore *ms) {
    ms->count = 2;

    // Market 0: Capital City — high tax, low transport cost
    Market *m0 = &ms->items[0];
    memset(m0, 0, sizeof(Market));
    strncpy(m0->name, "Capital City", 23);
    m0->trade_tax      = 0.08f;
    m0->transport_cost = 1.0f;

    // Market 1: Frontier Town — low tax, high transport cost
    Market *m1 = &ms->items[1];
    memset(m1, 0, sizeof(Market));
    strncpy(m1->name, "Frontier Town", 23);
    m1->trade_tax      = 0.03f;
    m1->transport_cost = 5.0f;
}

// ── Producers ─────────────────────────────────────────────────────────
// good_id, input_good_id (255=none), market_id
typedef struct { uint8_t good; uint8_t input; uint8_t market; int count; } PTemplate;

static void init_producers(ProducerStore *ps, int good_count) {
    (void)good_count;
    PTemplate templates[] = {
        { 0, 255, 0, 20 },  // grain farmers (no input), capital
        { 0, 255, 1, 15 },  // grain farmers, frontier
        { 1, 255, 0, 15 },  // iron miners
        { 1, 255, 1, 10 },  // iron miners, frontier
        { 2, 255, 0, 12 },  // cloth weavers
        { 3,   0, 0, 18 },  // food processors (grain→food)
        { 4,   1, 0, 14 },  // toolmakers (iron→tools)
        { 5,   2, 0,  8 },  // luxury makers (cloth→luxuries)
    };
    int nt = (int)(sizeof(templates) / sizeof(templates[0]));

    ps->count = 0;
    for (int t = 0; t < nt && ps->count < MAX_PRODUCERS; t++) {
        for (int k = 0; k < templates[t].count && ps->count < MAX_PRODUCERS; k++) {
            Producer *p = &ps->items[ps->count++];
            memset(p, 0, sizeof(Producer));
            p->good_id       = templates[t].good;
            p->input_good_id = templates[t].input;
            p->market_id     = templates[t].market;
            p->alive         = 1;
            p->capital       = PRODUCER_CAPITAL_BASE * (0.8f + lcg_randf() * 0.4f);
            p->efficiency    = 1.0f + lcg_randf() * 0.5f;
            p->labor_units   = 2.0f + lcg_randf() * 3.0f;
        }
    }
}

// ── Consumers ─────────────────────────────────────────────────────────
static void init_consumers(ConsumerStore *cs, int good_count) {
    cs->count = MAX_CONSUMERS;

    for (int i = 0; i < cs->count; i++) {
        Consumer *c = &cs->items[i];
        memset(c, 0, sizeof(Consumer));
        c->alive      = 1;
        c->market_id  = (i % 3 == 0) ? 1 : 0;  // 1/3 frontier
        c->income     = CONSUMER_INCOME_BASE * (0.5f + lcg_randf() * 1.5f);
        c->savings    = c->income * (2.0f + lcg_randf() * 3.0f);

        // Randomize preferences, then normalize
        float total = 0.0f;
        for (int g = 0; g < good_count; g++) {
            c->pref_weight[g] = 0.1f + lcg_randf() * 0.9f;
            total += c->pref_weight[g];
        }
        for (int g = 0; g < good_count; g++) {
            c->pref_weight[g] /= total;
        }
    }
}

// ── World ─────────────────────────────────────────────────────────────
void world_init(World *w) {
    memset(w, 0, sizeof(World));
    w->global_tech_level  = 0.0f;
    w->inflation_index    = 1.0f;

    init_goods(&w->goods);
    init_markets(&w->markets);
    init_producers(&w->producers, w->goods.count);
    init_consumers(&w->consumers, w->goods.count);

    // Estimate initial money supply
    w->total_money_supply = 0.0f;
    for (int i = 0; i < w->producers.count; i++)
        w->total_money_supply += w->producers.items[i].capital;
    for (int i = 0; i < w->consumers.count; i++)
        w->total_money_supply += w->consumers.items[i].savings;
}
