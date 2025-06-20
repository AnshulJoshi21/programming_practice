#include <raylib.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr char SCREEN_TITLE[] = "SNAKE";
constexpr Color SCREEN_BACKGROUND = LIGHTGRAY;
constexpr int GAME_FPS = 60;

int
main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}