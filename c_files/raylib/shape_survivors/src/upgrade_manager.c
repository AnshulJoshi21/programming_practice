#include "settings.h"
#include "upgrade_manager.h"
#include "utils.h"
#include <assert.h>

static const Upgrade upgrade_db[UPGRADE_TYPE_MAX] = {
    [UPGRADE_TYPE_PLAYER_SPEED]
    = {.name = "PLAYER SPEED", .description = "Increase Player Speed", .value = 10,},

    [UPGRADE_TYPE_PLAYER_MAX_HEALTH]
    = {.name = "PLAYER MAX HEALTH", .description = "Increase Player Max Health", .value = 10,},

    [UPGRADE_TYPE_PLAYER_RECOVER]
    = {.name = "PLAYER RECOVER HEALTH", .description = "Recover Player Health", .value = 10,},

    [UPGRADE_TYPE_BULLET_SPEED]
    = {.name = "BULLET SPEED", .description = "Increase Bullet Speed", .value = 10,},

    [UPGRADE_TYPE_BULLET_DAMAGE]
    = {.name = "BULLET DAMAGE", .description = "Increase Bullet Damage", .value = 1,},

    [UPGRADE_TYPE_BULLET_RANGE]
    = {.name = "BULLET RANGE", .description = "Increase Bullet Range", .value = 1,},
};

void upgrade_manager_init(UpgradeManager* um, Player* player) {
    assert(um);
    assert(player);

    um->player           = player;
    um->selected_upgrade = UPGRADE_TYPE_NONE;

    for (int i = 0; i < MAX_CHOICES; i++) {
        um->choices[i] = UPGRADE_TYPE_NONE;
    }
}

void upgrade_manager_reset(UpgradeManager* um) {
    assert(um);

    um->selected_upgrade = UPGRADE_TYPE_NONE;

    for (int i = 0; i < MAX_CHOICES; i++) {
        um->choices[i] = UPGRADE_TYPE_NONE;
    }
}

bool upgrade_manager_is_choices_empty(const UpgradeManager* um) {
    assert(um);

    for (int i = 0; i < MAX_CHOICES; i++) {
        if (um->choices[i] != UPGRADE_TYPE_NONE)
            return false;
    }

    return true;
}

void upgrade_manager_fill_choices(UpgradeManager* um) {
    assert(um);
    int upgrades[UPGRADE_TYPE_MAX];

    // generate array of all available upgrade indexes
    for (int i = 0; i < UPGRADE_TYPE_MAX; i++) {
        upgrades[i] = i;
    }

    // shuffle upgrades array - fisher yates algo
    for (int i = UPGRADE_TYPE_MAX - 1; i > 0; i--) {
        int random_index = GetRandomValue(0, i);

        // swap values
        int temp               = upgrades[i];
        upgrades[i]            = upgrades[random_index];
        upgrades[random_index] = temp;
    }

    // pick upgrades
    for (int i = 0; i < MAX_CHOICES; i++) {
        um->choices[i] = (UpgradeType) upgrades[i];
    }
}

void upgrade_manager_apply_upgrade(UpgradeManager* um) {
    assert(um);

    Player*        player  = um->player;
    const Upgrade* upgrade = &upgrade_db[um->selected_upgrade];

    switch (um->selected_upgrade) {
        case UPGRADE_TYPE_NONE:
            return;
        case UPGRADE_TYPE_PLAYER_SPEED:
            player->movement.speed += upgrade->value;
            break;
        case UPGRADE_TYPE_PLAYER_MAX_HEALTH:
            player->health.max += (int) upgrade->value;
            break;
        case UPGRADE_TYPE_PLAYER_RECOVER:
            player->health.current += (int) upgrade->value;
            break;
        case UPGRADE_TYPE_BULLET_SPEED:
            player->bullet_config.speed += upgrade->value;
            break;
        case UPGRADE_TYPE_BULLET_DAMAGE:
            player->bullet_config.damage += (int) upgrade->value;
            break;
        case UPGRADE_TYPE_BULLET_RANGE:
            player->bullet_config.lifetime += upgrade->value;
            break;
        default:
            return;
    }

    upgrade_manager_reset(um);
}

void upgrade_manager_draw(UpgradeManager* um, const Vector2 world_mouse) {
    assert(um);

    if (um->selected_upgrade != UPGRADE_TYPE_NONE)
        return;

    if (upgrade_manager_is_choices_empty(um))
        return;

    const float margin         = 100.0f;
    const float gap            = 50.0f;
    const float line_thickness = 5.0f;

    const float usable_width = BASE_WIDTH - (margin * 2);
    const float width        = (usable_width - (gap * (MAX_CHOICES - 1))) / MAX_CHOICES;
    const float height       = 150.0f;

    for (int i = 0; i < MAX_CHOICES; i++) {
        const Upgrade* choice = &upgrade_db[um->choices[i]];

        const float x = (width + gap) * i + margin;
        const float y = BASE_HEIGHT / 2.0f - height / 2.0f;

        const Rectangle rect    = (Rectangle){x, y, width, height};
        const bool      hovered = CheckCollisionPointRec(world_mouse, rect);
        const Color     color   = (hovered) ? RED : BLACK;

        if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            um->selected_upgrade = um->choices[i];
            return;
        }

        DrawRectangleLinesEx(rect, line_thickness, color);

        // draw text
        utils_center_and_draw_text(
            ORIGIN_TOP_LEFT, rect, &(CText){choice->name, 20.0f, 2.0f, BLACK});
        utils_center_and_draw_text(ORIGIN_TOP_LEFT,
                                   (Rectangle){rect.x, rect.y, rect.width, rect.height + 100},
                                   &(CText){choice->description, 10.0f, 2.0f, BLACK});
    }
}
