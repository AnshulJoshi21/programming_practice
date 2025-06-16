#include "../../include/menus/map_menu.h"
#include "../../include/databases/menus_database.h"
#include "../../include/game_states.h"
#include "../../include/menus/menu.h"
#include <raylib.h>

typedef enum MapMenuState
{
    SETTLEMENT,
    WILDERNESS,
    DUNGEON,
    MYSTICAL,
    CONFLICT,

    INVALID = -1,

} MapMenuState;

static MapMenuState current_map_menu_state = INVALID;

static Menu map_menu;

void
map_menu_init(int menu_vertical_padding)
{
    int font_size = 30;
    int text_gap = 20;
    Rectangle layout_rect =
      (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_vertical_padding };

    menu_init(
      &map_menu, map_menu_database, map_menu_database_size, font_size, text_gap, layout_rect);
}

void
map_menu_draw()
{
    menu_draw(&map_menu);
}

void
map_menu_update(GameState* current_state)
{
    menu_update(&map_menu);
    if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) && *current_state == STATE_MAP_MENU)
    {
        switch (map_menu.selected)
        {
            case SETTLEMENT:
                current_map_menu_state = SETTLEMENT;
                break;
            case WILDERNESS:
                current_map_menu_state = WILDERNESS;
                break;
            case DUNGEON:
                current_map_menu_state = DUNGEON;
                break;
            case MYSTICAL:
                current_map_menu_state = MYSTICAL;
                break;
            case CONFLICT:
                current_map_menu_state = CONFLICT;
                break;

            default:
                TraceLog(LOG_WARNING, "Invalied map menu selection: %d\n", map_menu.selected);
        }
    }
}

void
map_menu_free()
{
    menu_free(&map_menu);
}
