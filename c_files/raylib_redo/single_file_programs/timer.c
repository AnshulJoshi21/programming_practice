#include "timer.h"
#include <assert.h>
#include <raylib.h>

void interval_timer_init(IntervalTimer* timer, const float duration) {
    assert(timer);

    timer->elapsed  = GetTime();
    timer->duration = duration;
}

bool interval_timer_tick(IntervalTimer* timer) {
    assert(timer);

    const float current_time = GetTime();

    if (current_time - timer->elapsed >= timer->duration) {
        timer->elapsed = current_time;

        return true;
    }

    return false;
}
