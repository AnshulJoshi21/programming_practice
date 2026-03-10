#include "raylib.h"

#include <stdlib.h>

#define MAX_STARS 400
#define NUM_LAYERS 3

typedef struct Star
{
    Vector2 position;
    float speed;
    float size;
    Color color;
} Star;

// Helper to get a random color with varying alpha for "glow"
Color GetStarColor()
{
    int brightness = GetRandomValue(150, 255);
    return (Color){brightness, brightness, brightness,
                   GetRandomValue(100, 255)};
}

int main(void)
{
    const int screenWidth  = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "AAA Starfield - Raylib");

    Star stars[MAX_STARS];

    // Initialize stars with parallax layers
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].position = (Vector2){GetRandomValue(0, screenWidth),
                                      GetRandomValue(0, screenHeight)};

        // Assign layers: 0 (back) to 2 (front)
        int layer      = i % NUM_LAYERS;
        stars[i].speed = (layer + 1) * 0.5f; // Front layers move faster
        stars[i].size  = (layer + 1) * 0.8f; // Front layers are bigger
        stars[i].color = GetStarColor();
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update: Move stars to the left
        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].position.x -= stars[i].speed;

            // Wrap around screen
            if (stars[i].position.x < 0) {
                stars[i].position.x = screenWidth;
                stars[i].position.y = GetRandomValue(0, screenHeight);
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < MAX_STARS; i++) {
            // AAA Touch: Draw a subtle "glow" flare for closer stars
            if (stars[i].size > 1.5f) {
                DrawCircleGradient(stars[i].position.x, stars[i].position.y,
                                   stars[i].size * 2.0f, stars[i].color, BLANK);
            }

            DrawCircleV(stars[i].position, stars[i].size, stars[i].color);
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
