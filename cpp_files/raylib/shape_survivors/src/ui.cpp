#include "ui.hpp"
#include "utils.hpp"

void ui_player_xp_bar(const Player &player)
{
    const float margin = 50.0f;
    const float width = GetScreenWidth() - (margin * 2);
    const float height = 40.0f;
    const float x = GetScreenWidth() / 2.0f - width / 2.0f;
    const float y = 10.0f;

    const Rectangle bounds = {x, y, width, height};

    draw_progress_bar(player.xp.xp, player.xp.xp_next, bounds, 5.0f, BLACK,
                      LIGHTGRAY, SKYBLUE);

    center_and_draw_text(OriginType::top_left,
                         "LV " + std::to_string(player.level.current),
                         {bounds.x + bounds.width / 2.0f, bounds.y,
                          bounds.width / 2.0f, bounds.height},
                         20.0f, 2.0f, BLACK);
}
