#ifndef TIMER_H
#define TIMER_H

typedef struct {
    float elapsed;
    float duration;
} Timer;

int timer_tick(Timer* timer, const float dt);

#endif // TIMER_H
