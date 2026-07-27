#include "utils.hpp"
#include <random>

namespace utils {

float randf(const float min, const float max) {
    if (min == max)
        return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    static std::random_device             rd;
    static std::mt19937                   gen(rd());
    std::uniform_real_distribution<float> distr(minimum, maximum);

    return distr(gen);
}

void draw_centered_text(const OriginType type,
                        std::string      text,
                        const Rectangle  bounds,
                        const float      font_size,
                        const float      spacing,
                        const Color      tint) {
    const Font    font      = GetFontDefault();
    const Vector2 text_size = MeasureTextEx(font, text.c_str(), font_size, spacing);
    Vector2       pos       = {0, 0};

    switch (type) {
        case OriginType::CENTER:
            pos = {
                bounds.x - text_size.x / 2.0f,
                bounds.y - text_size.y / 2.0f,
            };
            break;

        case OriginType::TOP_LEFT:
            pos = {
                bounds.x + (bounds.width - text_size.x) / 2.0f,
                bounds.y + (bounds.height - text_size.y) / 2.0f,
            };
            break;

        default:
            return;
    }

    DrawTextEx(font, text.c_str(), pos, font_size, spacing, tint);
}
}; // namespace utils
