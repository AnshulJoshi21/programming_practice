#include "utils.hpp"
#include <algorithm>
#include <random>

float random_float(const int min, const int max)
{
    if (min == max)
        return min;

    const float minimum = std::min(min, max);
    const float maximum = std::max(min, max);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distr(minimum, maximum);

    return distr(gen);
}

void center_and_draw_text(const OriginType origin_type, const std::string text,
                          const Rectangle bounds, const float font_size,
                          const float spacing, const Color tint)
{
    const Font font = GetFontDefault();
    const Vector2 text_size = MeasureTextEx(font, text.c_str(), font_size,
                                            spacing);
    Vector2 pos = {0, 0};

    switch (origin_type) {
    case OriginType::center:
        pos = {
            bounds.x - (text_size.x / 2.0f),
            bounds.y - (text_size.y / 2.0f),
        };
        break;
    case OriginType::top_left:
        pos = {
            bounds.x + (bounds.width - text_size.x) / 2.0f,
            bounds.y + (bounds.height - text_size.y) / 2.0f,
        };
        break;
    }

    DrawTextEx(font, text.c_str(), pos, font_size, spacing, tint);
}

void draw_progress_bar(const int min, const int max, const Rectangle bounds,
                       const float thickness, const Color border_color,
                       const Color bg_color, const Color fill_color)
{
    // background
    DrawRectangleRec(bounds, bg_color);

    // progress bar
    float progress = (static_cast<float>(min) / static_cast<float>(max)) *
                     bounds.width;
    DrawRectangleRec({bounds.x, bounds.y, progress, bounds.height}, fill_color);

    // border
    DrawRectangleLinesEx(bounds, thickness, border_color);
}
