#include <raylib.h>

constexpr int BASE_WIDTH  = 1280;
constexpr int BASE_HEIGHT = 720;

int main(void) {
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Shape Survivors");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
