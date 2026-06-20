#include <raylib.h>

static const int BASE_WIDTH  = 800;
static const int BASE_HEIGHT = 600;

int main(void) {
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
