#pragma once

#include <raylib.h>
#include <string>

enum class OriginType {
    center,
    top_left,

};

float random_float(const int min, const int max);

void center_and_draw_text(const OriginType origin_type, const std::string text,
                          const Rectangle bounds, const float font_size = 20.0f,
                          const float spacing = 2.0f, const Color tint = WHITE);

void draw_progress_bar(const int min, const int max, const Rectangle bounds,
                       const float thickness, const Color border_color,
                       const Color bg_color, const Color fill_color);
