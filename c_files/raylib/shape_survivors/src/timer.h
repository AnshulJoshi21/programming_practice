#ifndef TIMER_H
#define TIMER_H

#include <raylib.h>

typedef struct {
    float elapsed;
    float interval;
} IntervalTimer;

void interval_timer_init(IntervalTimer* timer, const float interval);
bool interval_timer_tick(IntervalTimer* timer, const float dt);

#endif // TIMER_H
