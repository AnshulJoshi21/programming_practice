#include "utils.h"

// min/max functions

float
max_float(float a, float b)
{
	return (a > b) ? a : b;
}

float
min_float(float a, float b)
{
	return (a < b) ? a : b;
}

int
max_int(int a, int b)
{
	return (a > b) ? a : b;
}

int
min_int(int a, int b)
{
	return (a < b) ? a : b;
}

// interval timer

void
interval_timer_init(IntervalTimer* interval_timer, float interval_seconds)
{
	interval_timer->last_updated_time = GetTime();
	interval_timer->interval_seconds = interval_seconds;
	interval_timer->toggled = false;
}

void
interval_timer_update(IntervalTimer* interval_timer)
{
	float current_time = GetTime();
	if (current_time - interval_timer->last_updated_time >=
		interval_timer->interval_seconds) {
		interval_timer->last_updated_time = current_time;
		interval_timer->toggled = !interval_timer->toggled;
	}
}

bool
interval_timer_toggled(IntervalTimer* interval_timer)
{
	return interval_timer->toggled;
}

// center and draw text

void
center_and_draw_text(char* text,
					 int font_size,
					 int rect_x,
					 int rect_y,
					 int rect_width,
					 int rect_height,
					 Color color)
{
	int text_width = MeasureText(text, font_size);
	int text_x = rect_x + rect_width / 2 - text_width / 2;
	int text_y = rect_y + rect_height / 2 - font_size / 2;

	DrawText(text, text_x, text_y, font_size, color);
}
