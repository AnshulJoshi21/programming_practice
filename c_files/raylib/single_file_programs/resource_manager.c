#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH  = 1280;
static const int SCREEN_HEIGHT = 720;
static const int SHEET_ROWS    = 17;
static const int SHEET_COLS    = 6;
static const int SHEET_X       = 0;
static const int SHEET_Y       = 0;

static const float SCROLL_MIN = 0.125f;
static const float SCROLL_MAX = 64.0f;

static const int MAX_FRAMES = 20;

static void draw_spritesheet_grid(const Texture2D sheet) {
    const int sprite_width  = sheet.width / SHEET_COLS;
    const int sprite_height = sheet.height / SHEET_ROWS;

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

    const int sprite_width  = sheet.width / SHEET_COLS;
    const int sprite_height = sheet.height / SHEET_ROWS;

    Camera2D camera = (Camera2D){
        .offset   = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target   = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .rotation = 0.0f,
        .zoom     = 1.0f,
    };

    Vector2 selection_arr[MAX_FRAMES];
    int     selection_arr_size = 0;
    Color   selection_color    = BLUE;
    selection_color.a          = 80;

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
            Vector2 delta = GetMouseDelta();
            delta         = Vector2Scale(delta, -1.0f / camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }

        const Vector2 world_mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);
        const float   mouse_wheel     = GetMouseWheelMove();
        if (mouse_wheel != 0) {
            camera.offset = GetMousePosition();
            camera.target = world_mouse_pos;
            float scale   = 0.2f * mouse_wheel;
            camera.zoom *= expf(scale);
            camera.zoom = Clamp(camera.zoom, SCROLL_MIN, SCROLL_MAX);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            const int x                         = world_mouse_pos.x / sprite_width;
            const int y                         = world_mouse_pos.y / sprite_height;
            selection_arr[selection_arr_size++] = (Vector2){x, y};
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        DrawTexture(sheet, SHEET_X, SHEET_Y, WHITE);
        draw_spritesheet_grid(sheet);

        for (int i = 0; i < selection_arr_size; i++) {
            Vector2* pos = &selection_arr[i];
            DrawRectangleRec(
                (Rectangle){
                    pos->x * sprite_width, pos->y * sprite_height, sprite_width, sprite_height},
                selection_color);

            DrawText(TextFormat("Frame %d: (%d, %d)", i + 1, pos->x, pos->y),
                     sheet.width + 20,
                     100 + (i * 30),
                     20,
                     BLACK);
        }

        EndMode2D();

        EndDrawing();
    }

    UnloadTexture(sheet);

    CloseWindow();

    return 0;
}
