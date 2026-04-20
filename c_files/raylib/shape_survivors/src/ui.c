#include "settings.h"
#include "ui.h"
#include "utils.h"

#include <assert.h>

void ui_draw_player_xp_bar(const Player* player) {
    assert(player);

    const float x = 10.0f;
    const float y = 5.0f;
    const float width = SCREEN_WIDTH - (x * 2);
    const float height = 30.0f;

    const Rectangle dest = (Rectangle){x, y, width, height};
    const Color border_color = BLACK;
    const Color background_color = LIGHTGRAY;
    const Color fill_color = BLUE;

    draw_progress_bar(player->xp.xp_next, player->xp.xp, dest, 5.0f, background_color, border_color,
                      fill_color);

    // draw player level
    center_and_draw_text(ORIGIN_TOP_LEFT, TextFormat("LV %d", player->xp.level), dest, 16.0f, 2.0f,
                         border_color);
}
