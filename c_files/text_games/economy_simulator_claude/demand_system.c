#include "systems.h"
#include "config.h"
#include <math.h>

// ── Demand System ─────────────────────────────────────────────────────
// Each consumer:
//   1. Receives income (wage + savings interest)
//   2. Allocates budget across goods using weighted preferences
//   3. Adjusts preferences based on price changes (substitution effect)
//   4. Accumulates demand signal per good

void system_demand(World *w) {
    // Reset demand
    for (int g = 0; g < w->goods.count; g++) {
        w->goods.items[g].demand = 0.0f;
    }

    Consumer *consumers = w->consumers.items;
    int nc = w->consumers.count;
    int ng = w->goods.count;

    for (int i = 0; i < nc; i++) {
        Consumer *c = &consumers[i];
        if (!c->alive) continue;

        // Income + tiny savings yield
        float income = c->income + c->savings * 0.001f;
        c->savings += income * 0.1f; // save 10%
        float budget = income * 0.9f;

        // ── Preference adjustment (substitution effect) ───────────────
        // If a good's price rose above base, reduce weight for it
        float total_adj_weight = 0.0f;
        float adj_weight[MAX_GOODS];
        for (int g = 0; g < ng; g++) {
            float price_ratio = w->goods.items[g].price /
                                (w->goods.items[g].base_price + 0.001f);
            // luxury goods are more elastic
            float elasticity = w->goods.items[g].is_luxury ? 1.5f : 0.6f;
            adj_weight[g] = c->pref_weight[g] *
                            powf(1.0f / price_ratio, elasticity);
            total_adj_weight += adj_weight[g];
        }

        // ── Budget allocation & demand recording ──────────────────────
        c->spent_total = 0.0f;
        for (int g = 0; g < ng; g++) {
            if (total_adj_weight < 0.001f) break;
            float share   = adj_weight[g] / total_adj_weight;
            float spending = budget * share;
            float qty      = spending / (w->goods.items[g].price + 0.001f);
            c->bought[g]   = qty;
            c->spent_total += spending;
            w->goods.items[g].demand += qty;
        }

        // ── Utility (simple Cobb-Douglas proxy) ──────────────────────
        float utility = 0.0f;
        for (int g = 0; g < ng; g++) {
            if (c->pref_weight[g] > 0.01f && c->bought[g] > 0.0f) {
                utility += c->pref_weight[g] *
                           logf(c->bought[g] + 1.0f);
            }
        }
        c->utility = utility / (float)ng;
        c->ticks_alive++;
    }
}
