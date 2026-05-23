#include <raylib.h>

constexpr int BASE_WIDTH  = 800;
constexpr int BASE_HEIGHT = 600;

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
