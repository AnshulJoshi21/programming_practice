#include "../include/game_states.h"
#include "../include/menus/main_menu.h"
#include "../include/menus/map_menu.h"
#include "../include/menus/player_selection_menu.h"
#include "../include/menus/shop_menu.h"
#include "../include/menus/town_menu.h"
#include "../include/player.h"
#include <raylib.h>

int
main(void)
{
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;
    const char SCREEN_TITLE[] = "Text Rpg";
    const Color SCREEN_BACKGROUND = SKYBLUE;
    const int GAME_FPS = 60;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    GameState current_state = STATE_MAIN_MENU;
    int menu_vertical_padding = 40;
    bool player_selected = false;

    main_menu_init(menu_vertical_padding);
    player_selection_init(menu_vertical_padding);
    town_menu_init(menu_vertical_padding);
    map_menu_init(menu_vertical_padding);
    shop_menu_init(menu_vertical_padding);

    while (current_state != STATE_QUIT)
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            switch (current_state)
            {
                case STATE_MAIN_MENU:
                    break;
                case STATE_PLAYER_SELECTION_MENU:
                    current_state = STATE_MAIN_MENU;
                    break;
                case STATE_TOWN_MENU:
                    if (player_selected)
                    {
                        current_state = STATE_MAIN_MENU;
                    }
                    break;
                case STATE_MAP_MENU:
                    current_state = STATE_TOWN_MENU;
                    break;
                case STATE_QUEST_MENU:
                    current_state = STATE_TOWN_MENU;
                    break;
                case STATE_SHOP_MENU:
                    current_state = STATE_TOWN_MENU;
                    break;
                case STATE_QUIT:
                    current_state = STATE_QUIT;
                    break;
            }
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        switch (current_state)
        {
            case STATE_MAIN_MENU:
                main_menu_draw();
                main_menu_update(&current_state, player_selected);
                break;

            case STATE_PLAYER_SELECTION_MENU:
                player_selection_draw();
                Player player = player_selection_update(&current_state, &player_selected);
                break;

            case STATE_TOWN_MENU:
                town_menu_draw();
                town_menu_update(&current_state);
                break;

            case STATE_MAP_MENU:
                map_menu_draw();
                map_menu_update(&current_state);
                break;

            case STATE_QUEST_MENU:
                break;

            case STATE_SHOP_MENU:
                shop_menu_draw();
                shop_menu_update(&current_state);
                break;

            case STATE_QUIT:
                break;
        }

        EndDrawing();
    }

    main_menu_free();
    player_selection_free();
    town_menu_free();
    map_menu_free();
    shop_menu_free();

    CloseWindow();

    return 0;
}
