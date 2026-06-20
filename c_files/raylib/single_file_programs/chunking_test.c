#include <math.h>
#include <raylib.h>

#define BASE_WIDTH 800
#define BASE_HEIGHT 600

#define MAP_SIZE 5000

static void draw_background_grid() {
    const float thick      = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = 100.0f;

    for (int x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_SIZE}, thick, color);
    }
    for (int y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_SIZE, y}, thick, color);
    }
}

int main(void) {
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Chunking Test");
    SetTargetFPS(60);

    Camera2D camera = (Camera2D){
        .offset   = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
        .target   = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1.0f,
    };

    const float half_w = GetScreenWidth() / 2.0f;
    const float half_h = GetScreenHeight() / 2.0f;

    while (!WindowShouldClose()) {
        const Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);

        // update camera
        camera.target.x = fmaxf(half_w, fminf(mouse_pos.x, MAP_SIZE - half_w));
        camera.target.y = fmaxf(half_h, fminf(mouse_pos.y, MAP_SIZE - half_h));

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        draw_background_grid();

        EndMode2D();

        EndDrawing();
    }

    return 0;
}
