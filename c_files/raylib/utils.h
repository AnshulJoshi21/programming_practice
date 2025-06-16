#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

// min/max functions
float
max_float(float a, float b);
float
min_float(float a, float b);
int
max_int(int a, int b);
int
min_int(int a, int b);

// interval timer

typedef struct IntervalTimer
{
	float last_updated_time;
	float interval_seconds;
	bool toggled;

} IntervalTimer;

void
interval_timer_init(IntervalTimer* interval_timer, float interval_seconds);
void
interval_timer_update(IntervalTimer* interval_timer);
bool
interval_timer_toggled(IntervalTimer* interval_timer);

// center text

void
center_and_draw_text(char* text,
					 int font_size,
					 int rect_x,
					 int rect_y,
					 int rect_width,
					 int rect_height,
					 Color color);

#endif // UTILS_H