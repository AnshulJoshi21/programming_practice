#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

void utils_draw_background_grid(void);
void center_and_draw_text(const char *text, const Rectangle layout_rect,
                          const float font_size, const float spacing,
                          const Color tint);

#endif // UTILS_H
