#include "game_manager.h"
#include "settings.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int) time(NULL));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shape Survivors");

    const RenderTexture2D canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    SetTextureFilter(canvas.texture, TEXTURE_FILTER_BILINEAR);

    GameManager game_manager;
    game_manager_init(&game_manager);

    Vector2 mouse_pos = GetMousePosition();

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager_update(&game_manager, dt);

        BeginTextureMode(canvas);
        ClearBackground(LIGHTGRAY);

        game_manager_draw(&game_manager, mouse_pos);

        EndTextureMode();

        const float scale = fminf((float) GetScreenWidth() / (float) SCREEN_WIDTH,
                                  (float) GetScreenHeight() / (float) SCREEN_HEIGHT);
        const Vector2 offset = (Vector2){
            (GetScreenWidth() - (SCREEN_WIDTH * scale)) / 2.0f,
            (GetScreenHeight() - (SCREEN_HEIGHT * scale)) / 2.0f,
        };
        const Rectangle source = (Rectangle){0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT};
        const Rectangle dest =
            (Rectangle){offset.x, offset.y, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale};

        mouse_pos = (Vector2){GetMouseX() * scale, GetMouseY() * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
