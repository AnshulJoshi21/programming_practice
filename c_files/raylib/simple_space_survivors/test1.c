#include "raylib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define STAR_COUNT 600

typedef struct Star
{
    float x;
    float y;
    float speed;
    float size;
    float brightness;
} Star;

Star stars[STAR_COUNT];

void InitStars()
{
    for (int i = 0; i < STAR_COUNT; i++) {
        stars[i].x = GetRandomValue(0, SCREEN_WIDTH);
        stars[i].y = GetRandomValue(0, SCREEN_HEIGHT);

        stars[i].speed      = (float)GetRandomValue(10, 200) / 100.0f;
        stars[i].size       = (float)GetRandomValue(1, 3);
        stars[i].brightness = (float)GetRandomValue(150, 255);
    }
}

void UpdateStars(float dt)
{
    for (int i = 0; i < STAR_COUNT; i++) {
        stars[i].y += stars[i].speed * 60 * dt;

        if (stars[i].y > SCREEN_HEIGHT) {
            stars[i].y = 0;
            stars[i].x = GetRandomValue(0, SCREEN_WIDTH);
        }
    }
}

void DrawStars()
{
    for (int i = 0; i < STAR_COUNT; i++) {
        unsigned char b = stars[i].brightness;
        DrawCircle(stars[i].x, stars[i].y, stars[i].size,
                   (Color){b, b, b, 255});
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AAA Starfield");
    SetTargetFPS(60);

    InitStars();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        UpdateStars(dt);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawStars();

        EndDrawing();
    }

    CloseWindow();
}
