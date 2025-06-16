#include "../../include/menus/shop_menu.h"
#include "../../include/databases/menus_database.h"
#include "../../include/game_states.h"
#include "../../include/menus/menu.h"
#include <raylib.h>

typedef enum ShopMenuState
{
    CONSUMABLES,
    WEAPONS,
    ARMORS,
    ACCESSORIES,

    INVALID = -1,

} ShopMenuState;

static ShopMenuState current_shop_menu_state = INVALID;

static Menu shop_menu;

void
shop_menu_init(int menu_vertical_padding)
{
    int font_size = 30;
    int text_gap = 20;
    Rectangle layout_rect =
      (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_vertical_padding };

    menu_init(
      &shop_menu, shop_menu_database, shop_menu_database_size, font_size, text_gap, layout_rect);
}

void
shop_menu_draw()
{
    menu_draw(&shop_menu);
}

void
shop_menu_update(GameState* current_state)
{
    menu_update(&shop_menu);
    if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
        *current_state == STATE_SHOP_MENU)
    {
        switch (shop_menu.selected)
        {

            case CONSUMABLES:
                current_shop_menu_state = CONSUMABLES;
                break;
            case WEAPONS:
                current_shop_menu_state = WEAPONS;
                break;
            case ARMORS:
                current_shop_menu_state = ARMORS;
                break;
            case ACCESSORIES:
                current_shop_menu_state = ACCESSORIES;
                break;

            default:
                TraceLog(LOG_WARNING, "Invalied shop menu selection: %d\n", shop_menu.selected);
        }
    }
}

void
shop_menu_free()
{
    menu_free(&shop_menu);
}
