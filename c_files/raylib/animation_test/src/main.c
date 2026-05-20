#include "game_manager.h"
#include "settings.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Animation Test");
    SetTargetFPS(60);

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    GameManager game_manager;
    game_manager_init(&game_manager);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager_update(&game_manager, dt);

        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        game_manager_draw(&game_manager);

        EndTextureMode();

        const float scale
                = fminf((float)GetScreenWidth() / (float)BASE_WIDTH,
                        (float)GetScreenHeight() / (float)BASE_HEIGHT);
        const Vector2 offset = (Vector2){
                (GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
                (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f,
        };

        const Rectangle source = (Rectangle){0, 0, BASE_WIDTH, -BASE_HEIGHT};
        const Rectangle dest   = (Rectangle){offset.x,
                                             offset.y,
                                             source.width * scale,
                                             source.height * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture,
                       source,
                       dest,
                       (Vector2){0, 0},
                       0.0f,
                       WHITE);

        EndDrawing();
    }

    game_manager_shutdown(&game_manager);

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
