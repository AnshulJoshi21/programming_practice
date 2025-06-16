#define _GNU_SOURCE

#include "../../include/menus/player_selection_menu.h"
#include "../../include/databases/hero_types_database.h"
#include "../../include/menus/menu.h"
#include "../../include/player.h"
#include "../../include/utils.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LENGTH 64

static Menu player_selection_menu;

static void
draw_hero_type_summary(int selected)
{
    // draw line divider
    DrawLineEx((Vector2){ GetScreenWidth() / 2.0f, 0 },
               (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() },
               5.0,
               BLACK);

    char health[STR_LENGTH];
    char damage[STR_LENGTH];
    char defense[STR_LENGTH];
    char health_growth[STR_LENGTH];
    char damage_growth[STR_LENGTH];
    char defense_growth[STR_LENGTH];

    snprintf(health, STR_LENGTH, "Health: %0.2f\n", hero_types[selected].health);
    snprintf(damage, STR_LENGTH, "Damage: %0.2f\n", hero_types[selected].damage);
    snprintf(defense, STR_LENGTH, "Defense: %0.2f\n", hero_types[selected].defense);
    snprintf(
      health_growth, STR_LENGTH, "Health Growth: %0.2f\n", hero_types[selected].health_growth);
    snprintf(
      damage_growth, STR_LENGTH, "Damage Growth: %0.2f\n", hero_types[selected].damage_growth);
    snprintf(
      defense_growth, STR_LENGTH, "Defense Growth: %0.2f\n", hero_types[selected].defense_growth);

    const char* arr[] = { health, damage, defense, health_growth, damage_growth, defense_growth };
    const int arr_size = sizeof(arr) / sizeof(arr[0]);
    int vertical_padding = 40;
    int font_size = 30;
    int text_gap = 20;
    Rectangle layout_rect = (Rectangle){
        GetScreenWidth() / 2.0f, 0, GetScreenWidth() / 2.0f, GetScreenHeight() - vertical_padding
    };
    Color color = BLACK;

    center_and_draw_text_array(arr, arr_size, font_size, text_gap, layout_rect, color);
}

void
player_selection_init(int menu_vertical_padding)
{
    char** temp_arr = malloc(hero_types_size * sizeof(char*));
    if (temp_arr == NULL)
    {
        fprintf(stderr, "Memory not allocated\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < hero_types_size; i++)
    {
        temp_arr[i] = strndup(hero_types[i].type, strlen(hero_types[i].type) + 1);
    }

    int font_size = 30;
    int text_gap = 20;
    Rectangle layout_rect =
      (Rectangle){ 0, 0, GetScreenWidth() / 2.0f, GetScreenHeight() - menu_vertical_padding };

    menu_init(&player_selection_menu,
              ( const char* const* ) temp_arr,
              hero_types_size,
              font_size,
              text_gap,
              layout_rect);

    for (int i = 0; i < hero_types_size; i++)
    {
        free(temp_arr[i]);
        temp_arr[i] = NULL;
    }
    free(temp_arr);
    temp_arr = NULL;
}

void
player_selection_draw()
{
    menu_draw(&player_selection_menu);
}

Player
player_selection_update(GameState* current_state, bool* player_selected)
{
    menu_update(&player_selection_menu);
    draw_hero_type_summary(player_selection_menu.selected);

    if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
        *current_state == STATE_PLAYER_SELECTION_MENU)
    {
        *player_selected = true;
        *current_state = STATE_TOWN_MENU;

        return player_init(player_selection_menu.selected);
    }

    Player dummy_player = { 0 };
    return dummy_player;
}

void
player_selection_free()
{
    menu_free(&player_selection_menu);
}
