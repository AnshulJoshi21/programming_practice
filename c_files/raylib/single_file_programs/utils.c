#include "utils.h"

#include <assert.h>

void center_and_draw_text(const char *text, float font_size, float text_spacing,
                          Rectangle layout_rect, Color color)
{
    assert(text);

    Font font         = GetFontDefault();
    Vector2 text_size = MeasureTextEx(font, text, font_size, text_spacing);
    Vector2 position  = (Vector2){
        layout_rect.x + layout_rect.width / 2.0f - text_size.x / 2.0f,
        layout_rect.y + layout_rect.height / 2.0f - text_size.y / 2.0f,
    };

    DrawTextEx(font, text, position, font_size, text_spacing, color);
}

void scrollable_menu(const char **text_list, const int list_size,
                     float font_size, float spacing, float line_gap,
                     Rectangle layout_rect, Color color)
{
    assert(text_list);

    Font font       = GetFontDefault();
    int list_height = font_size * list_size + line_gap * (list_size - 1);

    for (int i = 0; i < list_size; i++) {
        Vector2 text_size =
            MeasureTextEx(font, text_list[i], font_size, spacing);
        Vector2 postion = (Vector2){
            layout_rect.x + layout_rect.width / 2.0f - text_size.x / 2.0f,
            layout_rect.y + layout_rect.height / 2.0f - list_height / 2.0f +
                i * (font_size + line_gap)};

        DrawTextEx(font, text_list[i], postion, font_size, spacing, color);
    }

    int scroll_offset = 0;

    if (IsKeyPressed(KEY_S)) {
        scroll_offset++;
    } else if (IsKeyPressed(KEY_W)) {
        scroll_offset--;
    }

    // selection arrow
    Vector2 text_size =
        MeasureTextEx(font, text_list[scroll_offset], font_size, spacing);
    Vector2 postion = (Vector2){
        layout_rect.x + layout_rect.width / 2.0f - text_size.x / 2.0f,
        layout_rect.y + layout_rect.height / 2.0f - list_height / 2.0f +
            scroll_offset * (font_size + line_gap)};

    DrawTextEx(font, "> ", postion, font_size, spacing, color);
}

// -- TIMER ---------------------------------//
void interval_timer_init(Timer *timer, float interval_duration)
{
    assert(timer);
    assert(interval_duration >= 0.0f);

    timer->start_time        = GetTime();
    timer->interval_duration = interval_duration;
}

bool interval_timer_update(Timer *timer)
{
    assert(timer);

    float current_time = GetTime();

    if (current_time - timer->start_time >= timer->interval_duration) {
        timer->start_time = current_time;

        return true;
    }

    return false;
}
