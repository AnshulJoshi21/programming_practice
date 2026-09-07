#include "game_manager.h"
#include "settings.h"
#include <raylib.h>

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shape Survivors");

    GameManager game_manager;
    game_manager_init(&game_manager);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager_update(&game_manager, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        game_manager_draw(&game_manager);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
