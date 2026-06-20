#ifndef UTILS_H
#define UTILS_H

#include "components.h"
#include <raylib.h>

typedef enum OriginType {
    ORIGIN_CENTER,
    ORIGIN_TOP_LEFT,
} OriginType;

void center_and_draw_text(const OriginType type, const CText* text, const Rectangle bounds);

#endif // UTILS_H
