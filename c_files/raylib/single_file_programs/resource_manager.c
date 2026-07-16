#include <assert.h>
#include <raylib.h>

static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 600;
static const int SHEET_ROWS    = 17;
static const int SHEET_COLS    = 6;
static const int SHEET_X       = 0;
static const int SHEET_Y       = 0;

static void draw_spritesheet_grid(const Texture2D sheet, const int rows, const int cols) {
    const int sprite_width  = sheet.width / cols;
    const int sprite_height = sheet.height / rows;

    const float thick = 2.0f;
    const Color color = BLACK;

    for (int x = (int) SHEET_X; x < sheet.width; x += sprite_width) {
        DrawLineEx((Vector2){x, SHEET_Y}, (Vector2){x, sheet.height}, thick, color);
    }
    for (int y = (int) SHEET_Y; y < sheet.height; y += sprite_height) {
        DrawLineEx((Vector2){SHEET_X, y}, (Vector2){sheet.width, y}, thick, color);
    }

    // outer rect
    DrawRectangleLinesEx((Rectangle){SHEET_X, SHEET_Y, sheet.width, sheet.height}, thick, color);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    const Texture2D sheet = LoadTexture("./asset/warrior_sheet_effect.png");
    assert(IsTextureValid(sheet));

    Camera2D camera = (Camera2D){
        .offset   = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target   = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .rotation = 0.0f,
        .zoom     = 1.0f,
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        DrawTexture(sheet, (int) SHEET_X, (int) SHEET_Y, WHITE);
        draw_spritesheet_grid(sheet, SHEET_ROWS, SHEET_COLS);

        EndMode2D();

        EndDrawing();
    }

    UnloadTexture(sheet);

    CloseWindow();

    return 0;
}
