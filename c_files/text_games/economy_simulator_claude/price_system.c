#include "systems.h"
#include "config.h"
#include <math.h>

// ── Price System ──────────────────────────────────────────────────────
// Walrasian tâtonnement: prices rise when demand > supply, fall otherwise.
// Formula:
//   excess_demand = (demand - supply) / (supply + epsilon)
//   price_next    = price * (1 + elasticity * excess_demand)
//
// Luxury goods are more volatile (higher elasticity multiplier).

void system_prices(World *w) {
    Good *goods = w->goods.items;
    int ng = w->goods.count;

    for (int g = 0; g < ng; g++) {
        Good *good = &goods[g];

        float supply  = good->supply  + 0.001f;
        float demand  = good->demand  + 0.001f;
        float excess  = (demand - supply) / supply;

        float elasticity = BASE_PRICE_ELASTICITY *
                           (good->is_luxury ? 2.0f : 1.0f);

        float new_price = good->price * (1.0f + elasticity * excess);

        // Apply inflation drift
        new_price *= (1.0f + INFLATION_RATE);

        // Clamp
        if (new_price < PRICE_FLOOR) new_price = PRICE_FLOOR;
        if (new_price > PRICE_CEIL)  new_price = PRICE_CEIL;

        good->price = new_price;

        // ── Price history ring buffer ─────────────────────────────────
        good->price_history[good->history_head] = new_price;
        good->history_head = (good->history_head + 1) % 52;
    }
}
