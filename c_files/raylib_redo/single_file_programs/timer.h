#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

typedef struct IntervalTimer {
    float elapsed;
    float duration;

} IntervalTimer;

void interval_timer_init(IntervalTimer* timer, const float duration);
bool interval_timer_tick(IntervalTimer* timer);

#endif // TIMER_H
