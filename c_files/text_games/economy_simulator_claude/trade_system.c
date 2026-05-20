#include "systems.h"
#include "config.h"
#include <math.h>

// ── Trade System ──────────────────────────────────────────────────────
// Market clearing:
//   traded_volume = min(supply, demand)
//   Revenue distributed to producers proportional to their output share.
//   Market collects trade_tax fraction.

void system_trade(World *w) {
    Good     *goods     = w->goods.items;
    Producer *producers = w->producers.items;
    Market   *markets   = w->markets.items;
    int ng = w->goods.count;
    int np = w->producers.count;
    int nm = w->markets.count;

    // Reset GDP
    for (int m = 0; m < nm; m++) {
        markets[m].total_gdp = 0.0f;
    }

    // ── Clear each good's market ───────────────────────────────────────
    for (int g = 0; g < ng; g++) {
        Good *good = &goods[g];
        float supply = good->supply;
        float demand = good->demand;
        float traded = fminf(supply, demand);
        good->traded_volume = traded;

        float total_revenue = traded * good->price;

        // Distribute revenue to producers of this good
        // proportional to their output share
        if (supply < 0.001f) continue;

        for (int i = 0; i < np; i++) {
            Producer *p = &producers[i];
            if (!p->alive || p->good_id != g) continue;

            float share   = p->output_last / supply;
            float revenue = total_revenue * share;
            float tax     = revenue * markets[p->market_id].trade_tax;

            p->capital          += (revenue - tax);
            p->profit_last       = (revenue - tax) - p->output_last * WAGE_RATE;
            p->cumulative_profit += p->profit_last;

            markets[p->market_id].total_gdp += revenue;
        }
    }

    // ── GDP history ────────────────────────────────────────────────────
    for (int m = 0; m < nm; m++) {
        Market *mkt = &markets[m];
        mkt->gdp_history[mkt->gdp_head] = mkt->total_gdp;
        mkt->gdp_head = (mkt->gdp_head + 1) % 52;
        mkt->tick++;
    }
}
