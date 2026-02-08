#include <raylib.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "";
static const Color SCREEN_BACKGROUND = RAYWHITE;
static const int GAME_FPS            = 60;

// == MAIN ===========================================
int main(void)
{
    // == INIT ===========================================
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    while (!WindowShouldClose()) {
        // == UPDATE ===========================================

        // == DRAW ===========================================
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
