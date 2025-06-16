#include "../../include/menus/main_menu.h"
#include "../../include/game_states.h"
#include "../../include/menus/menu.h"
#include "../../include/databases/menus_database.h"
#include <raylib.h>

typedef enum MainMenuState
{
    NEW_GAME,
    CONTINUE,
    QUIT,

} MainMenuState;

static Menu main_menu;

void
main_menu_init(int menu_vertical_padding)
{
    int font_size = 40;
    int text_gap = 20;
    Rectangle layout_rect =
      (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_vertical_padding };

    menu_init(
      &main_menu, main_menu_database, main_menu_database_size, font_size, text_gap, layout_rect);
}

void
main_menu_draw()
{
    menu_draw(&main_menu);
}

void
main_menu_update(GameState* current_state, bool player_selected)
{
    menu_update(&main_menu);
    if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
        *current_state == STATE_MAIN_MENU)
    {
        switch (main_menu.selected)
        {
            case NEW_GAME:
                *current_state = STATE_PLAYER_SELECTION_MENU;
                break;

            case CONTINUE:
                if (player_selected)
                {
                    *current_state = STATE_TOWN_MENU;
                }
                else
                {
                    main_menu.color = GRAY;
                }
                break;

            case QUIT:
                *current_state = STATE_QUIT;
                break;

            default:
                TraceLog(LOG_WARNING, "Invalied main menu selection: %d\n", main_menu.selected);
        }
    }
}

void
main_menu_free()
{
    menu_free(&main_menu);
}