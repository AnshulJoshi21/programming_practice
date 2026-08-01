#include <assert.h>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct Timer {
    float elapsed;
    float duration;
} Timer;

static void timer_init(Timer* timer, const float duration) {
    assert(timer);

    timer->elapsed  = GetTime();
    timer->duration = duration;
}

static bool timer_tick(Timer* timer) {
    assert(timer);

    const float current_time = GetTime();
    if (current_time - timer->elapsed >= timer->duration) {
        timer->elapsed += timer->duration;
        return true;
    }
    return false;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    Timer timer;
    timer_init(&timer, 0.01f);

    const Texture2D fire = LoadTexture("./fire_01.png");
    const Color     firePalette[36]
        = {{7, 7, 7, 255},       {31, 7, 7, 255},      {47, 15, 7, 255},     {71, 15, 7, 255},
           {87, 23, 7, 255},     {103, 31, 7, 255},    {119, 31, 7, 255},    {143, 39, 7, 255},
           {159, 47, 7, 255},    {175, 63, 7, 255},    {191, 71, 7, 255},    {199, 71, 7, 255},
           {223, 79, 7, 255},    {223, 87, 7, 255},    {223, 87, 7, 255},    {215, 95, 7, 255},
           {215, 103, 15, 255},  {207, 111, 15, 255},  {207, 119, 15, 255},  {207, 127, 15, 255},
           {207, 135, 23, 255},  {199, 135, 23, 255},  {199, 143, 23, 255},  {199, 151, 31, 255},
           {191, 159, 31, 255},  {191, 159, 31, 255},  {191, 167, 39, 255},  {191, 167, 39, 255},
           {191, 175, 47, 255},  {183, 175, 47, 255},  {183, 183, 47, 255},  {183, 183, 55, 255},
           {207, 207, 111, 255}, {223, 223, 159, 255}, {239, 239, 199, 255}, {255, 255, 255, 255}};

    static const Color FireGradient[8] = {
        {255, 255, 255, 255}, // White
        {255, 250, 200, 255}, // Light Yellow
        {255, 220, 70, 255},  // Yellow
        {255, 160, 20, 255},  // Orange
        {220, 100, 0, 255},   // Dark Orange
        {190, 35, 0, 255},    // Red
        {100, 10, 0, 255},    // Dark Red
        {0, 0, 0, 255},       // Black
    };

    int count = 0;

    while (!WindowShouldClose()) {
        if (timer_tick(&timer)) {
            count++;
            if (count >= 36) {
                count = 0;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(
            fire,
            (Rectangle){0, 0, fire.width, fire.height},
            (Rectangle){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, fire.width, fire.height},
            (Vector2){fire.width / 2.0f, fire.height / 2.0f},
            0.0f,
            firePalette[count]);

        EndDrawing();
    }

    UnloadTexture(fire);

    CloseWindow();

    return 0;
}
