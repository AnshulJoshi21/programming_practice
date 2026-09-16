#include "timer.h"
#include <assert.h>

void interval_timer_init(IntervalTimer* timer, const float interval) {
    assert(timer);

    timer->elapsed  = 0.0f;
    timer->interval = interval;
}

bool interval_timer_tick(IntervalTimer* timer, const float dt) {
    assert(timer);

    timer->elapsed += dt;
    if (timer->elapsed >= timer->interval) {
        timer->elapsed = 0.0f;
        return true;
    }
    return false;
}
