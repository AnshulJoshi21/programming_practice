#include "systems.h"
#include "config.h"

// ── Macro System ─────────────────────────────────────────────────────
// Global economy-wide effects run once per tick:
//   - Tech level grows → raises producer efficiency
//   - Inflation index tracked
//   - Money supply = sum of all agent capital + consumer savings

void system_macro(World *w) {
    // ── Technology growth ─────────────────────────────────────────────
    w->global_tech_level += TECH_GROWTH_RATE;

    // ── Inflation index ────────────────────────────────────────────────
    w->inflation_index *= (1.0f + INFLATION_RATE);

    // ── Money supply tracking ──────────────────────────────────────────
    float total = 0.0f;
    for (int i = 0; i < w->producers.count; i++) {
        if (w->producers.items[i].alive)
            total += w->producers.items[i].capital;
    }
    for (int i = 0; i < w->consumers.count; i++) {
        if (w->consumers.items[i].alive)
            total += w->consumers.items[i].savings;
    }
    w->total_money_supply = total;
}

// ── Stats helpers ─────────────────────────────────────────────────────
float world_gdp(const World *w) {
    float gdp = 0.0f;
    for (int m = 0; m < w->markets.count; m++) {
        gdp += w->markets.items[m].total_gdp;
    }
    return gdp;
}

float world_avg_price(const World *w, int good_id) {
    return w->goods.items[good_id].price;
}

float world_unemployment(const World *w) {
    // Unemployment proxy: producers whose labor fell below 1.0
    int total = 0, idle = 0;
    for (int i = 0; i < w->producers.count; i++) {
        const Producer *p = &w->producers.items[i];
        if (!p->alive) continue;
        total++;
        if (p->labor_units < 1.0f) idle++;
    }
    if (total == 0) return 0.0f;
    return (float)idle / (float)total;
}
