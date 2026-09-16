#include <assert.h>
#include <raylib.h>

static const int SCREEN_WIDTH  = 1280;
static const int SCREEN_HEIGHT = 720;

static const char* main_menu_title = "Main Menu";
static const char* main_menu[]     = {"New Game", "Settings", "Quit"};
static const int   main_menu_size  = sizeof(main_menu) / sizeof(main_menu[0]);

static void draw_menu(const char*     menu_title,
                      const char**    menu,
                      const int       menu_size,
                      const Rectangle bounds,
                      const float     font_size,
                      const Color     tint,
                      const Color     selected_tint,
                      const int       selected) {
    assert(menu_title);
    assert(menu);

    const Font  font     = GetFontDefault();
    const float spacing  = 2.0f;
    const float line_gap = 10.0f;

    // draw menu title
    const Vector2 title_text_size = MeasureTextEx(font, menu_title, font_size + 10.0f, spacing);
    const Vector2 title_pos = (Vector2){((bounds.x + bounds.width) - title_text_size.x) / 2.0f,
                                        bounds.y - title_text_size.y - 20.0f};
    DrawTextEx(font, menu_title, title_pos, title_text_size.y, spacing, BLACK);

    //
    const float total_text_height = (font_size * menu_size) + ((menu_size - 1) * line_gap);
    const float left_margin       = 20.0f;

    for (int i = 0; i < menu_size; i++) {
        const Vector2 pos = (Vector2){
            bounds.x + left_margin,
            bounds.y + (bounds.height - total_text_height) / 2.0f + ((font_size + line_gap) * i),
        };

        if (selected == i)
            DrawTextEx(font, TextFormat("> %s", menu[i]), pos, font_size, spacing, selected_tint);
        else
            DrawTextEx(font, TextFormat(" %s", menu[i]), pos, font_size, spacing, tint);
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Menu Test");
    SetTargetFPS(60);

    int selected          = 0;
    int current_menu_size = main_menu_size;

    // bounds rect
    const float     width  = 300.0f;
    const float     height = 300.0f;
    const Rectangle bounds = (Rectangle){20.0f, (GetScreenHeight() - height) / 2.0f, width, height};

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP) && selected > 0) selected--;
        if (IsKeyPressed(KEY_DOWN) && selected < current_menu_size - 1) selected++;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_menu(main_menu_title, main_menu, main_menu_size, bounds, 20.0f, GRAY, BLACK, selected);

        DrawRectangleLinesEx(bounds, 5.0f, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
