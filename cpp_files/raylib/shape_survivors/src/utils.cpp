#include "utils.hpp"

namespace Utils {

void center_and_draw_text(const OriginType        origin_type,
                          const Rectangle         bounds,
                          const Components::Text& text) {
    const Font    font      = GetFontDefault();
    const Vector2 text_size = MeasureTextEx(font, text.text.c_str(), text.font_size, text.spacing);
    Vector2       pos       = {0, 0};

    if (origin_type == OriginType::CENTER) {
        pos = {bounds.x - text_size.x / 2.0f, bounds.y - text_size.y / 2.0f};
    } else if (origin_type == OriginType::TOP_LEFT) {
        pos = {
            bounds.x + (bounds.width - text_size.x) / 2.0f,
            bounds.y + (bounds.height - text_size.y) / 2.0f,
        };
    }

    DrawTextEx(font, text.text.c_str(), pos, text.font_size, text.spacing, text.tint);
}

void draw_progress_bar(const int       min,
                       const int       max,
                       const Rectangle bounds,
                       const float     line_thickness,
                       const Color     line_color,
                       const Color     bg_color,
                       const Color     fill_color) {
    // background rect
    DrawRectangleRec(bounds, bg_color);

    // progress rect
    const float progress_width = (static_cast<float>(min) / static_cast<float>(max)) * bounds.width;
    const Rectangle progress_rect = {bounds.x, bounds.y, progress_width, bounds.height};

    DrawRectangleRec(progress_rect, fill_color);

    // line rect
    DrawRectangleLinesEx(bounds, line_thickness, line_color);
}

} // namespace Utils
