#pragma once

#include <raylib.h>
#include <string>

enum class OriginType {
    CENTER,
    TOP_LEFT,
};

struct IntervalTimer {
    float elapsed = GetTime();
    float interval;

    bool tick(void) {
        const float current_time = GetTime();
        if (current_time - elapsed >= interval) {
            elapsed = current_time;
            return true;
        }
        return false;
    }
};

namespace utils {

float randf(const float min, const float max);

void draw_centered_text(const OriginType type,
                        std::string      text,
                        const Rectangle  bounds,
                        const float      font_size,
                        const float      spacing,
                        const Color      tint);

}; // namespace utils
