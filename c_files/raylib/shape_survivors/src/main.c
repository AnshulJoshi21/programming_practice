#include "../include/game_manager.h"
#include "../include/settings.h"

#include <raylib.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    GameManager gm;
    game_manager_init(&gm);

    while (!WindowShouldClose()) {

        const float dt = GetFrameTime();

        game_manager_update(&gm, dt);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        game_manager_draw(&gm);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
