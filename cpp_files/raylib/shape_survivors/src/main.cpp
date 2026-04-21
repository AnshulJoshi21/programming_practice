#include "game_manager.hpp"
#include "settings.hpp"
#include <raylib.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shape Survivors");

    GameManager game_manager;

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager.update(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        game_manager.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
