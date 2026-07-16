#include "game_manager.hpp"
#include "settings.hpp"
#include <algorithm>
#include <cassert>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Survivors Clone");

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    GameManager game_manager;

    Vector2 world_mouse = {0, 0};

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager.update(dt);

        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        game_manager.draw(world_mouse);

        EndTextureMode();

        const float scale
            = std::min(static_cast<float>(GetScreenWidth()) / static_cast<float>(BASE_WIDTH),
                       static_cast<float>(GetScreenHeight()) / static_cast<float>(BASE_HEIGHT));

        const Vector2 offset = {(GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
                                (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f};

        const Rectangle source = {0, 0, BASE_WIDTH, -BASE_HEIGHT};
        const Rectangle dest   = {offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale};

        const Vector2 screen_mouse = GetMousePosition();

        world_mouse = {(screen_mouse.x - offset.x) / scale, (screen_mouse.y - offset.y) / scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, {0, 0}, 0.0, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
