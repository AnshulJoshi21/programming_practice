#include "utils.h"
#include <assert.h>
#include <stdlib.h>

float random_float(const float min, const float max) {
  if (min == max)
    return min;

  const float minimum = (min < max) ? min : max;
  const float maximum = (min < max) ? max : min;

  return minimum + ((float)rand() / (float)RAND_MAX) * (maximum - minimum);
}

void center_and_draw_text(const OriginType type, const char *text,
                          const Rectangle bounds, const float font_size,
                          const float spacing, const Color tint) {
  assert(text);

  const Font font = GetFontDefault();
  const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
  Vector2 pos = (Vector2){bounds.x, bounds.y};

  switch (type) {
  case ORIGIN_CENTER:
    pos = (Vector2){
        bounds.x - (text_size.x) / 2.0f,
        bounds.y - (text_size.y) / 2.0f,
    };
    break;
  case ORIGIN_TOP_LEFT:
    pos = (Vector2){
        bounds.x + (bounds.width - text_size.x) / 2.0f,
        bounds.y + (bounds.height - text_size.y) / 2.0f,
    };
    break;
  }

  DrawTextEx(font, text, pos, font_size, spacing, tint);
}

void draw_progress_bar(const int min, const int max, const Rectangle bounds,
                       const float border_thickness, const Color bg_color,
                       const Color fill_color, const Color border_color) {

  // background
  DrawRectangleRec(bounds, bg_color);

  // progress
  const float progress_width = ((float)min / (float)max) * bounds.width;

  DrawRectangleRec(
      (Rectangle){bounds.x, bounds.y, progress_width, bounds.height},
      fill_color);

  // border
  DrawRectangleLinesEx(bounds, border_thickness, border_color);
}
