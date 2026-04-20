#include <math.h>
#include <raylib.h>

int main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    const RenderTexture canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!WindowShouldClose()) {
        BeginTextureMode(canvas);

        EndTextureMode();

        const float scale =
            fminf((float) GetScreenWidth() / (float) SCREEN_WIDTH,
                  (float) GetScreenHeight() / (float) SCREEN_HEIGHT);
        const Vector2 offset = (Vector2){
            (GetScreenWidth() - (SCREEN_WIDTH * scale)) / 2.0f,
            (GetScreenHeight() - (SCREEN_HEIGHT * scale)) / 2.0f,
        };
        const Rectangle source = (Rectangle){0, 0, SCREEN_WIDTH,
                                             -SCREEN_HEIGHT};
        const Rectangle dest = (Rectangle){offset.x, offset.y,
                                           SCREEN_WIDTH * scale,
                                           SCREEN_HEIGHT * scale};

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f,
                       WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
