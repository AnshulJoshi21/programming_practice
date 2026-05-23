#include <algorithm>
#include <cassert>
#include <raylib.h>

constexpr int BASE_WIDTH  = 800;
constexpr int BASE_HEIGHT = 600;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    while (!WindowShouldClose()) {
        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
        EndTextureMode();

        const float scale =
            std::min(static_cast<float>(GetScreenWidth()) / static_cast<float>(BASE_WIDTH),
                     static_cast<float>(GetScreenHeight()) / static_cast<float>(BASE_HEIGHT));
        const Vector2 offset = {
            (GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
            (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f,
        };

        const Rectangle source = {0, 0, BASE_WIDTH, BASE_HEIGHT};
        const Rectangle dest   = {offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, {0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
