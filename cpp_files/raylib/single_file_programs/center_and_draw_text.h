#pragma once

#include <raylib.h>

void center_and_draw_text(const char *text, Rectangle layout_rect,
                          Font font = GetFontDefault(), float font_size = 30.0f,
                          float spacing = 2.0f, Color color = BLACK);
