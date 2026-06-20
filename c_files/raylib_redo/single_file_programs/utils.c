#include "utils.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>

static int rand_initialized = 0;

static void init_rand(void) {
    if (!rand_initialized) {
        srand((unsigned) time(NULL));
        rand_initialized = 1;
    }
}

float randf(const float min, const float max) {
    init_rand();

    if (min == max)
        return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float) rand() / (float) RAND_MAX) * (maximum - minimum);
}

void center_and_draw_text(const OriginType type,
                          const Rectangle  bounds,
                          const char*      text,
                          const float      font_size,
                          const float      spacing,
                          const Color      tint) {
    assert(text);

    const Font font = GetFontDefault();

    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    Vector2       pos;

    switch (type) {
        case ORIGIN_CENTER:
            pos = (Vector2){
                bounds.x - text_size.x / 2.0f,
                bounds.y - text_size.y / 2.0f,
            };
            break;

        case ORIGIN_TOP_LEFT:
            pos = (Vector2){
                bounds.x + (bounds.width - text_size.x) / 2.0f,
                bounds.y + (bounds.height - text_size.y) / 2.0f,
            };
            break;

        default:
            return;
    }

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}
