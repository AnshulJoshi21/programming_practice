#pragma once

#include "components.hpp"
#include <algorithm>
#include <random>
#include <raylib.h>

namespace Utils {

enum class OriginType {
    CENTER,
    TOP_LEFT,
};

static inline float randf(const float min, const float max) {
    if (min == max)
        return min;

    const float minimum = std::min(min, max);
    const float maximum = std::min(min, max);

    static std::random_device             rd;
    static std::mt19937                   gen(rd());
    std::uniform_real_distribution<float> distr(minimum, maximum);

    return distr(gen);
}

void center_and_draw_text(const OriginType        origin_type,
                          const Rectangle         bounds,
                          const Components::Text& text);

void draw_progress_bar(const int       min,
                       const int       max,
                       const Rectangle bounds,
                       const float     line_thickness,
                       const Color     line_color,
                       const Color     bg_color,
                       const Color     fill_color);

} // namespace Utils
