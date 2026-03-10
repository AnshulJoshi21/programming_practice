#include "../include/game_manager.h"
#include "../include/settings.h"

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand((unsigned int)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    const Texture2D spritesheet = LoadTexture("spritesheet.png");

    GameManager gm;
    game_manager_init(&gm);

    while (!WindowShouldClose()) {

        const float dt = GetFrameTime();

        game_manager_update(&gm, dt);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        game_manager_draw(&gm, spritesheet);

        EndDrawing();
    }

    UnloadTexture(spritesheet);

    CloseWindow();

    return 0;
}
