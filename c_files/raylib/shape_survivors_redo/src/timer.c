#include "timer.h"
#include <assert.h>

void timer_interval_init(IntervalTimer* it, const float interval) {
    assert(it);

    it->elapsed  = GetTime();
    it->interval = interval;
}

bool timer_interval_tick(IntervalTimer* it) {
    assert(it);

    const float current_time = GetTime();
    if (current_time - it->elapsed >= it->interval) {
        it->elapsed = current_time;
        return true;
    }
    return false;
}
