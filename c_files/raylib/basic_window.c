#include <raylib.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "";
static const Color SCREEN_BACKGROUND = RAYWHITE;

//-- MAIN ---------------------------------------//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 2.UPDATE

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
