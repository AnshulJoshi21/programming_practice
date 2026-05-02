#include <raylib.h>

#define BASE_WIDTH 1920
#define BASE_HEIGHT 1080

int main(void) {
  InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
