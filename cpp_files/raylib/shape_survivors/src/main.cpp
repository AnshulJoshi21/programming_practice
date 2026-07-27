#include "game_manager.hpp"
#include "settings.hpp"
#include <algorithm>
#include <cassert>
#include <raylib.h>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shape Survivors");

    RenderTexture canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    {
        GameManager game_manager;

        Vector2 world_mouse = {0, 0};

        while (!WindowShouldClose()) {
            const float dt = GetFrameTime();

            game_manager.update(dt);

            BeginTextureMode(canvas);
            ClearBackground(RAYWHITE);

            game_manager.draw(world_mouse);

            EndTextureMode();

            const float scale = std::min(
                static_cast<float>(GetScreenWidth()) / static_cast<float>(SCREEN_WIDTH),
                static_cast<float>(GetScreenHeight()) / static_cast<float>(SCREEN_HEIGHT));
            const Vector2 offset = {
                (GetScreenWidth() - (SCREEN_WIDTH * scale)) / 2.0f,
                (GetScreenHeight() - (SCREEN_HEIGHT * scale)) / 2.0f,
            };

            const Rectangle source = {0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT};
            const Rectangle dest
                = {offset.x, offset.y, source.width * scale, source.height * scale};

            const Vector2 screen_mouse = GetMousePosition();
            world_mouse                = {
                (screen_mouse.x - offset.x) / scale,
                (screen_mouse.y - offset.y) / scale,
            };

            BeginDrawing();
            ClearBackground(BLACK);

            DrawTexturePro(canvas.texture, source, dest, {0, 0}, 0.0f, WHITE);

            EndDrawing();
        }
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
