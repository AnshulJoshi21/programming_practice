#include "timer.h"
#include <assert.h>

int timer_tick(Timer* timer, const float dt) {
    assert(timer);

    timer->elapsed += dt;
    if (timer->elapsed >= timer->duration) {
        timer->elapsed = 0.0f;

        return 1;
    }
    return 0;
}
