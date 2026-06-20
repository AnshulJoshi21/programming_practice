#include "utils.h"
#include <assert.h>

void center_and_draw_text(const OriginType type, const CText* text, const Rectangle bounds) {
    assert(text);

    const Font    font      = GetFontDefault();
    const Vector2 text_size = MeasureTextEx(font, text->text, text->font_size, text->spacing);
    Vector2       pos;

    if (type == ORIGIN_CENTER) {
        pos = (Vector2){
            bounds.x - text_size.x / 2.0f,
            bounds.y - text_size.y / 2.0f,
        };
    } else if (type == ORIGIN_TOP_LEFT) {
        pos = (Vector2){
            bounds.x + (bounds.width - text_size.x) / 2.0f,
            bounds.y + (bounds.height - text_size.y) / 2.0f,
        };
    }

    DrawTextEx(font, text->text, pos, text->font_size, text->spacing, text->tint);
}
