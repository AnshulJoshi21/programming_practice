#include "settings.hpp"
#include "ui_manager.hpp"
#include "utils.hpp"

UiManager::UiManager(const Player& player, const EnemyManager& enemy_manager)
    : player(player), enemy_manager(enemy_manager) {}

void UiManager::draw_player_xp_bar(void) {
    const float     margin = 50.0f;
    const Rectangle bounds = {margin, 10.0f, BASE_WIDTH - margin * 2, 30.0f};

    Utils::draw_progress_bar(
        player.xp.current, player.xp.next, bounds, 3.0f, BLACK, LIGHTGRAY, BLUE);

    // draw player level
    const float offset = 5.0f;
    DrawText(TextFormat("LV %d", player.level.current),
             static_cast<int>(BASE_WIDTH - margin * 2),
             static_cast<int>(bounds.y + bounds.height + offset),
             20,
             BLACK);
}

void UiManager::draw_player_hp_bar(void) {
    const float width  = player.rect.width + 10;
    const float height = 10.0f;
    const float x      = player.position.x - width / 2.0f;
    const float y      = player.position.y - player.rect.height / 2.0f - height * 2;

    Utils::draw_progress_bar(player.health.current,
                             player.health.max,
                             {x, y, width, height},
                             1.0f,
                             BLACK,
                             LIGHTGRAY,
                             GREEN);
}

void UiManager::draw_enemy_hp_bar(void) {
    for (const Enemy& enemy : enemy_manager.enemies) {
        const float width  = enemy.rect.width + 10;
        const float height = 10.0f;
        const float x      = enemy.position.x - width / 2.0f;
        const float y      = enemy.position.y - enemy.rect.height / 2.0 - height * 2;

        Utils::draw_progress_bar(enemy.health.current,
                                 enemy.health.max,
                                 {x, y, width, height},
                                 1.0f,
                                 BLACK,
                                 LIGHTGRAY,
                                 RED);
    }
}
