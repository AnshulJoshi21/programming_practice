#include <raylib.h>

static const int SCREEN_WIDTH  = 1280;
static const int SCREEN_HEIGHT = 720;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
