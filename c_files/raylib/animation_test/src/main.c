#include "game_manager.h"
#include "settings.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Platformer Test");

    RenderTexture canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    GameManager game_manager;
    game_manager_init(&game_manager);

    Vector2 world_mouse;

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager_update(&game_manager, dt, world_mouse);

        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        game_manager_draw(&game_manager);

        EndTextureMode();

        const float   scale  = fminf((float) GetScreenWidth() / (float) SCREEN_WIDTH,
                                  (float) GetScreenHeight() / (float) SCREEN_HEIGHT);
        const Vector2 offset = (Vector2){(GetScreenWidth() - (SCREEN_WIDTH * scale)) / 2.0f,
                                         (GetScreenHeight() - (SCREEN_HEIGHT * scale)) / 2.0f};

        const Rectangle source = (Rectangle){0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT};
        const Rectangle dest
            = (Rectangle){offset.x, offset.y, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale};

        const Vector2 screen_mouse = GetMousePosition();

        world_mouse = (Vector2){
            (screen_mouse.x - offset.x) / scale,
            (screen_mouse.y - offset.y) / scale,
        };

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    game_manager_shutdown(&game_manager);

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
