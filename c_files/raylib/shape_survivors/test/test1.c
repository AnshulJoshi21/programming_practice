#include <assert.h>
#include <math.h>
#include <raylib.h>

#define BASE_WIDTH 800
#define BASE_HEIGHT 600

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    Vector2 world_mouse = (Vector2){0, 0};

    while (!WindowShouldClose()) {
        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        DrawText(
            TextFormat("Pos: (%0.2f, %0.2f)", world_mouse.x, world_mouse.y), 10, 10, 20, BLACK);

        EndTextureMode();

        const float   scale  = fminf((float) GetScreenWidth() / (float) BASE_WIDTH,
                                  (float) GetScreenHeight() / (float) BASE_HEIGHT);
        const Vector2 offset = (Vector2){(GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
                                         (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f};

        const Rectangle source = (Rectangle){0, 0, BASE_WIDTH, -BASE_HEIGHT};
        const Rectangle dest
            = (Rectangle){offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale};

        const Vector2 screen_mouse = GetMousePosition();

        world_mouse = (Vector2){
            (screen_mouse.x - offset.x) / scale,
            (screen_mouse.y - offset.y) / scale,
        };

        world_mouse.x = fmaxf(0.0f, fminf(world_mouse.x, BASE_WIDTH));
        world_mouse.y = fmaxf(0.0f, fminf(world_mouse.y, BASE_HEIGHT));

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
