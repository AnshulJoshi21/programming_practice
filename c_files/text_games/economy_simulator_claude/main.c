#include <stdio.h>
#include <string.h>
#include "economy_data.h"
#include "systems.h"
#include "world_init.h"
#include "config.h"

// ── Sparkline renderer ────────────────────────────────────────────────
// Renders a ring-buffer of 16 floats as ASCII sparkline
static void sparkline(const float *ring, int len, uint8_t head) {
    // Find min/max across the ring
    float mn = ring[0], mx = ring[0];
    for (int i = 1; i < len; i++) {
        if (ring[i] < mn) mn = ring[i];
        if (ring[i] > mx) mx = ring[i];
    }
    const char *bars = " ▁▂▃▄▅▆▇█";
    // Show last 16 entries
    int show = len < 16 ? len : 16;
    int start = (head - show + len) % len;
    for (int i = 0; i < show; i++) {
        float v = ring[(start + i) % len];
        float norm = (mx > mn) ? (v - mn) / (mx - mn) : 0.5f;
        int idx = (int)(norm * 8.0f);
        if (idx > 8) idx = 8;
        // Print UTF-8 bar character (3 bytes)
        const char *bar = bars + idx * 3;
        // bars is a UTF-8 string; each block glyph is 3 bytes except space
        // Simple approach: just index by codepoint offset
        // Rewrite using byte offsets
        (void)bar;
        // Fallback to ASCII since terminal may not support UTF-8 bars
        static const char ascii_bars[] = " ._-=+*#@";
        putchar(ascii_bars[idx]);
    }
}

// ── Display ───────────────────────────────────────────────────────────
static void display(const World *w) {
    int tick = (int)w->tick;
    int year  = tick / TICKS_PER_YEAR + 1;
    int week  = tick % TICKS_PER_YEAR + 1;

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║  ECONOMY SIMULATOR  ·  Year %-3d  Week %-2d  (tick %-4d)        ║\n",
           year, week, tick);
    printf("╠══════════════════════════════════════════════════════════════╣\n");

    // ── Macro stats ───────────────────────────────────────────────────
    float gdp  = world_gdp(w);
    float unem = world_unemployment(w) * 100.0f;
    printf("║  GDP: %10.1f  │  Inflation×: %6.4f  │  Tech: %.4f       ║\n",
           gdp, w->inflation_index, w->global_tech_level);
    printf("║  Money Supply: %10.1f  │  Unemployment: %5.1f%%          ║\n",
           w->total_money_supply, unem);
    printf("╠════════════════════════════════════════════╤═════════════════╣\n");

    // ── Goods table ───────────────────────────────────────────────────
    printf("║  %-12s  %7s  %8s  %8s  │  Price trend    ║\n",
           "Good", "Price", "Supply", "Demand");
    printf("║  ────────────  ───────  ────────  ────────  │  ─────────────  ║\n");
    for (int g = 0; g < w->goods.count; g++) {
        const Good *good = &w->goods.items[g];
        char trend = (good->supply < good->demand) ? '^' : (good->supply > good->demand ? 'v' : '=');
        printf("║  %-12s  %7.2f  %8.1f  %8.1f %c │  ",
               good->name, good->price, good->supply, good->demand, trend);
        sparkline(good->price_history, 52, good->history_head);
        printf("  ║\n");
    }

    // ── Markets ───────────────────────────────────────────────────────
    printf("╠════════════════════════════════════════════╧═════════════════╣\n");
    printf("║  Markets:                                                    ║\n");
    for (int m = 0; m < w->markets.count; m++) {
        const Market *mkt = &w->markets.items[m];
        printf("║    %-15s  GDP/tick: %10.1f  Tax: %.0f%%             ║\n",
               mkt->name, mkt->total_gdp, mkt->trade_tax * 100.0f);
    }

    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

// ── Main ──────────────────────────────────────────────────────────────
int main(void) {
    World w;
    world_init(&w);

    printf("Economy Simulator — DOD Architecture in C\n");
    printf("Producers: %d  Consumers: %d  Goods: %d  Markets: %d\n",
           w.producers.count, w.consumers.count,
           w.goods.count, w.markets.count);
    printf("Running %d ticks (%d simulated years)...\n\n",
           SIM_TICKS, SIM_TICKS / TICKS_PER_YEAR);

    for (int t = 0; t < SIM_TICKS; t++) {
        w.tick = (uint32_t)t;

        // ── System execution order matters ────────────────────────────
        // Production reads last-tick prices to decide output
        // Demand reads current prices
        // Trade clears the market
        // Prices adjust for next tick
        // Macro runs global effects

        system_production(&w);
        system_demand(&w);
        system_trade(&w);
        system_prices(&w);
        system_macro(&w);

        if (t % DISPLAY_TICKS == 0 || t == SIM_TICKS - 1) {
            display(&w);
        }
    }

    printf("\nSimulation complete. Final state:\n");
    printf("  GDP (last tick): %.1f\n", world_gdp(&w));
    printf("  Inflation index: %.4f (%.1f%% total inflation)\n",
           w.inflation_index, (w.inflation_index - 1.0f) * 100.0f);
    printf("  Tech level: %.4f\n", w.global_tech_level);
    return 0;
}
