#include "settings.h"
#include "upgrade_manager.h"
#include "utils.h"

#include <assert.h>

static const Upgrade upgrade_db[UPGRADE_MAX] = {
    [UPGRADE_PLAYER_HP] = {.name = "Player HP", .desc = "Increase max health"},
    [UPGRADE_PLAYER_SPEED] = {.name = "Player Speed", .desc = "Move faster"},
    [UPGRADE_BULLET_SPEED] = {.name = "Bullet Speed", .desc = "Bullets travel faster"},
    [UPGRADE_BULLET_DAMAGE] = {.name = "Bullet Damage", .desc = "Deal more damage"},
    [UPGRADE_BULLET_RATE] = {.name = "Bullet Rate", .desc = "Shoot more frequently"},
    [UPGRADE_BULLET_RANGE] = {.name = "Bullet Range", .desc = "Bullet travel further"},
};

void upgrade_manager_reset(UpgradeManager* um) {
    assert(um);

    for (int i = 0; i < MAX_CHOICES; i++) {
        um->choices[i] = UPGRADE_NONE;
    }
    um->current_choice = UPGRADE_NONE;
}

void upgrade_manager_init(UpgradeManager* um) {
    assert(um);

    upgrade_manager_reset(um);
}

void upgrade_manager_draw(UpgradeManager* um, const Vector2 mouse_pos) {
    assert(um);
    if (um->choices[0] == UPGRADE_NONE) {
        return;
    }

    const float margin = 50;
    const float gap = 30;
    const float width = (SCREEN_WIDTH - (margin * 2) - (gap * (MAX_CHOICES - 1))) / MAX_CHOICES;
    const float height = 150.0f;
    const float y = (SCREEN_HEIGHT - height) / 2.0f;

    for (int i = 0; i < MAX_CHOICES; i++) {
        const float x = i * (width + gap) + margin;

        // outline rect
        const Rectangle bg_rect = (Rectangle){x, y, width, height};
        const bool is_hovered = (CheckCollisionPointRec(mouse_pos, bg_rect));

        const Color bg_color = (is_hovered) ? RED : BLACK;

        if (is_hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            um->current_choice = um->choices[i];
            break;
        }

        DrawRectangleLinesEx(bg_rect, 3.0f, bg_color);

        const Upgrade current_upgrade = upgrade_db[um->choices[i]];

        // name
        center_and_draw_text(ORIGIN_TOP_LEFT, current_upgrade.name,
                             (Rectangle){x, y, width, height / 2.0f}, 20.0f, 2.0f, BLACK);
        // description
        center_and_draw_text(ORIGIN_TOP_LEFT, current_upgrade.desc,
                             (Rectangle){x, y + height / 2.0f, width, height / 2.0f}, 10.0f, 2.0f,
                             BLACK);
    }
}

static void _fill_choices_array(UpgradeManager* um) {
    assert(um);

    for (int i = 0; i < MAX_CHOICES; i++) {
        um->choices[i] = GetRandomValue(UPGRADE_PLAYER_HP, UPGRADE_BULLET_RANGE);
    }
}

static void _apply_upgrade_player(const UpgradeManager* um, Player* player) {
    assert(um);

    switch (um->current_choice) {
        case UPGRADE_PLAYER_HP:
            player->health.max_hp += 50;
            player->health.hp += 50;
            break;
        case UPGRADE_PLAYER_SPEED:
            player->move.speed += 20;
            break;
        case UPGRADE_BULLET_SPEED:
            player->bullet_config.speed += 20.0f;
            break;
        case UPGRADE_BULLET_DAMAGE:
            player->bullet_config.damage += 1;
            break;
        case UPGRADE_BULLET_RANGE:
            player->bullet_config.lifetime += 0.5f;
            break;
        case UPGRADE_BULLET_RATE:
            player->bullet_timer.interval *= 0.85f;
            break;
        default:
            break;
    }
}

void upgrade_manager_update(UpgradeManager* um, Player* player) {
    assert(um);

    if (um->choices[0] == UPGRADE_NONE) {
        _fill_choices_array(um);
    }

    if (um->current_choice != UPGRADE_NONE) {
        _apply_upgrade_player(um, player);
        upgrade_manager_reset(um);
    }
}
