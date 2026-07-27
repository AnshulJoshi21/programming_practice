#ifndef TIMER_H
#define TIMER_H

#include <raylib.h>

typedef struct IntervalTimer {
    float elapsed;
    float interval;
} IntervalTimer;

void timer_interval_init(IntervalTimer* it, const float interval);
bool timer_interval_tick(IntervalTimer* it);

#endif // TIMER_H
