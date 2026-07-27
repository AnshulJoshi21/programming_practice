#include "game_manager.h"
#include "settings.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned) time(NULL));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Shape Survivors");

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    GameManager game_manager;
    game_manager_init(&game_manager);

    Vector2 world_mouse = (Vector2){0, 0};

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager_update(&game_manager, dt);

        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        game_manager_draw(&game_manager, world_mouse);

        EndTextureMode();

        const float   scale  = fminf((float) GetScreenWidth() / (float) BASE_WIDTH,
                                  (float) GetScreenHeight() / (float) BASE_HEIGHT);
        const Vector2 offset = (Vector2){(GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
                                         (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f};

        const Rectangle source = (Rectangle){0, 0, BASE_WIDTH, -BASE_HEIGHT};
        const Rectangle dest
            = (Rectangle){offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale};

        const Vector2 screen_mouse = GetMousePosition();

        world_mouse = (Vector2){
            (screen_mouse.x - offset.x) / scale,
            (screen_mouse.y - offset.y) / scale,
        };

        world_mouse.x = fmaxf(0.0f, fminf(world_mouse.x, BASE_WIDTH));
        world_mouse.y = fmaxf(0.0f, fminf(world_mouse.y, BASE_HEIGHT));

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
