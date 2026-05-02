#include "game_manager.h"
#include "settings.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  srand(time(NULL));

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(BASE_WIDTH, BASE_HEIGHT, "Shape Survivors");

  const RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
  assert(IsRenderTextureValid(canvas));

  GameManager game_manager;
  game_manager_init(&game_manager);

  while (!WindowShouldClose()) {

    const float dt = GetFrameTime();

    game_manager_update(&game_manager, dt);

    BeginTextureMode(canvas);
    ClearBackground(RAYWHITE);

    game_manager_draw(&game_manager);

    EndTextureMode();

    const float scale = fminf((float)GetScreenWidth() / (float)BASE_WIDTH,
                              (float)GetScreenHeight() / (float)BASE_HEIGHT);
    const Vector2 offset = (Vector2){
        (GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
        (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f,
    };
    const Rectangle source = (Rectangle){0, 0, BASE_WIDTH, BASE_HEIGHT};
    const Rectangle dest = (Rectangle){offset.x, offset.y, BASE_WIDTH * scale,
                                       BASE_HEIGHT * scale};

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

    EndDrawing();
  }

  UnloadRenderTexture(canvas);

  CloseWindow();

  return 0;
}
