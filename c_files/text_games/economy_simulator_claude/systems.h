#pragma once
#include "economy_data.h"

// Production System — producers decide output, consume inputs, earn revenue
void system_production(World *w);

// Demand System — consumers allocate income across goods
void system_demand(World *w);

// Price System — prices adjust to supply/demand imbalances
void system_prices(World *w);

// Trade System — clears the market, matches supply to demand
void system_trade(World *w);

// Macro System — inflation, tech growth, money supply tracking
void system_macro(World *w);

// Stats helpers
float world_avg_price(const World *w, int good_id);
float world_gdp(const World *w);
float world_unemployment(const World *w);
