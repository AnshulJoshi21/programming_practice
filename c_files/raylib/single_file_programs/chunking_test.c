#include "raylib.h"

#include <math.h>
#include <stdio.h>

// --- Configuration ---
#define CHUNK_SIZE 64     // Size of one chunk in pixels (64x64)
#define RENDER_DISTANCE 7 // How many chunks to draw around the player
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// --- Helper: Pseudo-random color based on chunk coordinates ---
// This simulates "loading" data. If you go back to chunk (5,5),
// it will always be the same color.
Color GetChunkColor(int chunkX, int chunkY)
{
    // A simple hash function to generate a deterministic number from X and Y
    unsigned int hash = (chunkX * 73856093) ^ (chunkY * 19349663);

    // Use the hash to pick a color
    int r = (hash & 0xFF0000) >> 16;
    int g = (hash & 0x00FF00) >> 8;
    int b = (hash & 0x0000FF);

    return (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib - Basic Chunking Example");
    SetTargetFPS(60);

    // Setup a camera to move around the world
    Camera2D camera = {0};
    camera.zoom     = 1.0f;
    camera.offset =
        (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}; // Center player

    // Player position in World Space (Pixels)
    Vector2 playerPos = {0.0f, 0.0f};
    float speed       = 200.0f;

    while (!WindowShouldClose()) {
        // --- Update ---
        float dt = GetFrameTime();

        // 1. Move Player
        if (IsKeyDown(KEY_W))
            playerPos.y -= speed * dt;
        if (IsKeyDown(KEY_S))
            playerPos.y += speed * dt;
        if (IsKeyDown(KEY_A))
            playerPos.x -= speed * dt;
        if (IsKeyDown(KEY_D))
            playerPos.x += speed * dt;

        // 2. Camera follows player
        camera.target = playerPos;

        // 3. Calculate which Chunk the player is currently inside
        // Using floor() ensures we handle negative coordinates correctly
        int playerChunkX = (int)floorf(playerPos.x / CHUNK_SIZE);
        int playerChunkY = (int)floorf(playerPos.y / CHUNK_SIZE);

        // --- Draw ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        // 4. CHUNKING LOOP
        // Only loop through coordinates within RENDER_DISTANCE of the player
        int chunksDrawn = 0;

        for (int y = -RENDER_DISTANCE; y <= RENDER_DISTANCE; y++) {
            for (int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; x++) {

                // Calculate the actual World Chunk Coordinate
                int currentChunkX = playerChunkX + x;
                int currentChunkY = playerChunkY + y;

                // Calculate where to draw this chunk in pixel space
                int drawX = currentChunkX * CHUNK_SIZE;
                int drawY = currentChunkY * CHUNK_SIZE;

                // Get "Data" (Color) for this chunk
                Color chunkColor = GetChunkColor(currentChunkX, currentChunkY);

                // Draw the Chunk
                DrawRectangle(drawX, drawY, CHUNK_SIZE, CHUNK_SIZE, chunkColor);
                DrawRectangleLines(drawX, drawY, CHUNK_SIZE, CHUNK_SIZE,
                                   DARKGRAY);

                // Debug: Draw coordinate text inside chunk (optional)
                if (camera.zoom >= 1.0f) {
                    char coordText[32];
                    sprintf(coordText, "%d,%d", currentChunkX, currentChunkY);
                    DrawText(coordText, drawX + 5, drawY + 5, 10, BLACK);
                }

                chunksDrawn++;
            }
        }

        // Draw Player
        DrawCircleV(playerPos, 10, RED);

        EndMode2D();

        // UI Overlay
        DrawRectangle(10, 10, 220, 90, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 220, 90, BLUE);
        DrawText("WASD to Move", 20, 20, 20, BLACK);
        DrawText(
            TextFormat("Current Chunk: [%d, %d]", playerChunkX, playerChunkY),
            20, 50, 10, BLACK);
        DrawText(TextFormat("Chunks Rendered: %d", chunksDrawn), 20, 70, 10,
                 BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
