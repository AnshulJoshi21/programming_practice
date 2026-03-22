#include "../include/game_manager.h"
#include "../include/settings.h"

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    GameManager game_manager;
    game_manager_init(&game_manager);

    while (!WindowShouldClose()) {

        const float dt = GetFrameTime();

        game_manager_update(&game_manager, dt);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        game_manager_draw(&game_manager);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
