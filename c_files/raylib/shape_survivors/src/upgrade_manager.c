#include "settings.h"
#include "upgrade_manager.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>

void upgrade_manager_init(UpgradeManager* um, Player* player) {
    assert(um);
    assert(player);

    um->player           = player;
    um->selected_upgrade = NULL;

    for (int i = 0; i < MAX_CHOICES; i++) {
        um->choices[i] = (Upgrade){0};
    }
}

void upgrade_manager_update(UpgradeManager* um) {
    assert(um);
}

void upgrade_manager_draw(UpgradeManager* um, const Vector2 world_mouse) {
    assert(um);

    const float margin         = 100.0f;
    const float gap            = 50.0f;
    const float line_thickness = 5.0f;

    const float usable_width = BASE_WIDTH - (margin * 2);
    const float width        = (usable_width - (gap * 2)) / MAX_CHOICES;
    const float height       = 150.0f;

    for (int i = 0; i < MAX_CHOICES; i++) {
        const Upgrade* choice = &um->choices[i];
        assert(choice->type != UPGRADE_TYPE_MAX);

        const float x = (width + gap) * i + margin;
        const float y = BASE_HEIGHT / 2.0f - height / 2.0f;

        const Rectangle rect  = (Rectangle){x, y, width, height};
        const Color     color = (CheckCollisionPointRec(world_mouse, rect)) ? RED : BLACK;

        DrawRectangleLinesEx(rect, line_thickness, color);

        // draw text
        utils_center_and_draw_text(ORIGIN_TOP_LEFT, choice->name, rect, 20.0f, 2.0f, BLACK);
        utils_center_and_draw_text(ORIGIN_TOP_LEFT,
                                   choice->description,
                                   (Rectangle){rect.x, rect.y, rect.width, rect.height + 100},
                                   10.0f,
                                   2.0f,
                                   BLACK);
    }
}
