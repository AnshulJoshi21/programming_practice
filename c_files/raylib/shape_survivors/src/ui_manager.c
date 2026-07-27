#include "settings.h"
#include "ui_manager.h"
#include "utils.h"
#include <assert.h>

void ui_manager_init(UiManager* ui, const Player* player, const EnemyManager* enemy_manager) {
    assert(ui);
    assert(player);
    assert(enemy_manager);

    ui->player        = player;
    ui->enemy_manager = enemy_manager;
}

void ui_manager_player_health_bar(const UiManager* ui) {
    assert(ui);

    const Player* player = ui->player;

    const float bar_offset    = 5.0f;
    const float bounds_width  = 60.0f;
    const float bounds_height = 10.0f;

    const float line_thickness = 2.0f;
    const Color line_color     = BLACK;
    const Color bg_color       = LIGHTGRAY;
    const Color fill_color     = DARKGREEN;

    // player health bar
    const Rectangle player_bounds
        = (Rectangle){player->position.x - bounds_width / 2.0f,
                      player->position.y - player->rect.height / 2.0f - bar_offset - bounds_height,
                      bounds_width,
                      bounds_height};

    utils_draw_progress_bar(player->health.current,
                            player->health.max,
                            player_bounds,
                            line_thickness,
                            line_color,
                            bg_color,
                            fill_color);
}

void ui_manager_enemy_health_bar(const UiManager* ui) {
    assert(ui);
    const EnemyManager* enemy_manager = ui->enemy_manager;

    const float bar_offset    = 5.0f;
    const float bounds_width  = 60.0f;
    const float bounds_height = 10.0f;

    const float line_thickness = 2.0f;
    const Color line_color     = BLACK;
    const Color bg_color       = LIGHTGRAY;
    const Color fill_color     = RED;

    // enemy health bars
    for (int i = 0; i < enemy_manager->spawner.current; i++) {
        const Enemy* enemy = &enemy_manager->enemies[i];

        const Rectangle enemy_bounds = (Rectangle){enemy->position.x - bounds_width / 2.0f,
                                                   enemy->position.y - enemy->rect.height / 2.0f
                                                       - bar_offset - bounds_height,
                                                   bounds_width,
                                                   bounds_height};

        utils_draw_progress_bar(enemy->health.current,
                                enemy->health.max,
                                enemy_bounds,
                                line_thickness,
                                line_color,
                                bg_color,
                                fill_color);
    }
}

void ui_manager_player_xp_bar(const UiManager* ui) {
    assert(ui);
    const Player* player = ui->player;

    // progress bar
    const float     bounds_width  = BASE_WIDTH - 100.0f;
    const float     bounds_height = 30.0f;
    const Rectangle bounds        = (Rectangle){
        (BASE_WIDTH - bounds_width) / 2.0f,
        20.0f,
        bounds_width,
        bounds_height,
    };

    utils_draw_progress_bar(
        player->xp.current, player->xp.next, bounds, 3.0f, BLACK, LIGHTGRAY, BLUE);

    // draw player level
    const float text_x = BASE_WIDTH - bounds.x - 50.0f;
    const float text_y = bounds.y + bounds_height + 5.0f;
    DrawText(TextFormat("Lv %d", player->level.current), text_x, text_y, 20.0f, BLACK);
}
