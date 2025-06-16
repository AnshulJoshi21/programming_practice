#include "../../include/menus/town_menu.h"
#include "../../include/game_states.h"
#include "../../include/menus/menu.h"
#include "../../include/databases/menus_database.h"
#include <raylib.h>

typedef enum TownMenuState
{
    MAP,
    QUEST,
    SHOP,

} TownMenuState;

static Menu town_menu;

void
town_menu_init(int menu_vertical_padding)
{
    int font_size = 30;
    int text_gap = 20;
    Rectangle layout_rect = (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() };

    menu_init(
      &town_menu, town_menu_database, town_menu_database_size, font_size, text_gap, layout_rect);
}

void
town_menu_draw()
{
    menu_draw(&town_menu);
}

void
town_menu_update(GameState* current_state)
{
    menu_update(&town_menu);

    if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
        *current_state == STATE_TOWN_MENU)
    {
        switch (town_menu.selected)
        {
            case MAP:
                *current_state = STATE_MAP_MENU;
                break;
            case QUEST:
                *current_state = STATE_QUEST_MENU;
                break;
            case SHOP:
                *current_state = STATE_SHOP_MENU;
                break;
            default:
                TraceLog(LOG_WARNING, "Invalied town menu selection: %d\n", town_menu.selected);
        }
    }
}

void
town_menu_free()
{
    menu_free(&town_menu);
}
