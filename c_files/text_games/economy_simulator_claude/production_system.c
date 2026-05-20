#include "systems.h"
#include "config.h"
#include <math.h>

// ── Production System ──────────────────────────────────────────────────
// Each producer:
//   1. Checks input good price vs capital to decide labor
//   2. Produces output = labor * efficiency * tech_boost
//   3. Adds output to market supply
//   4. Pays wage bill, earns revenue from last tick's sales
// Pure SoA-friendly iteration — no pointer chasing.

void system_production(World *w) {
    float tech_boost = 1.0f + w->global_tech_level;

    // Reset supply for all goods this tick
    for (int g = 0; g < w->goods.count; g++) {
        w->goods.items[g].supply = 0.0f;
    }

    Producer *producers = w->producers.items;
    int n = w->producers.count;

    for (int i = 0; i < n; i++) {
        Producer *p = &producers[i];
        if (!p->alive) continue;

        Good *out_good = &w->goods.items[p->good_id];

        // ── Input cost check ──────────────────────────────────────────
        float input_cost = 0.0f;
        if (p->input_good_id < 255) {
            Good *in_good = &w->goods.items[p->input_good_id];
            // each labor unit consumes 0.5 input goods
            input_cost = p->labor_units * 0.5f * in_good->price;
        }

        float wage_bill = p->labor_units * WAGE_RATE;
        float total_cost = wage_bill + input_cost;

        // ── Capital-constrained production ────────────────────────────
        // If can't afford full labor, scale down
        if (total_cost > p->capital && total_cost > 0.0f) {
            float scale = p->capital / total_cost;
            p->labor_units *= scale;
            total_cost = p->labor_units * WAGE_RATE +
                         (p->input_good_id < 255
                              ? p->labor_units * 0.5f * w->goods.items[p->input_good_id].price
                              : 0.0f);
        }

        // ── Output ────────────────────────────────────────────────────
        float output = p->labor_units * p->efficiency * tech_boost;
        p->output_last = output;
        out_good->supply += output;
        p->capital -= total_cost;

        // ── Profit-driven labor adjustment (next tick) ────────────────
        // Simple rule: if last profit > 0 and price trending up → hire more
        float price_ratio = out_good->price / (out_good->base_price + 0.001f);
        float desired_scale = 0.8f + 0.4f * fminf(price_ratio, 2.0f);
        p->target_labor = p->labor_units * desired_scale;
        // Clamp labor change to ±20% per tick (hiring/firing friction)
        float delta = p->target_labor - p->labor_units;
        p->labor_units += delta * 0.2f;
        if (p->labor_units < 0.1f) p->labor_units = 0.1f;
        if (p->labor_units > 50.0f) p->labor_units = 50.0f;

        p->ticks_alive++;
    }
}
