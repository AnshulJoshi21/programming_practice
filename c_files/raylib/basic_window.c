#include <raylib.h>

#define BASE_WIDTH 800
#define BASE_HEIGHT 600

int main(void) {
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    return 0;
}
