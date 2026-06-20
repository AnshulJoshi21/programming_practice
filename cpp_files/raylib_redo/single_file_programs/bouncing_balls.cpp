#include <algorithm>
#include <array>
#include <assert.h>
#include <random>
#include <raylib.h>
#include <raymath.h>

constexpr int BASE_WIDTH  = 800;
constexpr int BASE_HEIGHT = 600;
constexpr int MAX_BALLS   = 200;

static inline float randf(const float min, const float max) {
    if (min == max)
        return min;

    const float minimum = std::min(min, max);
    const float maximum = std::max(min, max);

    static std::random_device             rd;
    static std::mt19937                   gen(rd());
    std::uniform_real_distribution<float> distr(minimum, maximum);

    return distr(gen);
}

class Ball {
  public:
    float   radius;
    Vector2 center;
    float   speed;
    Vector2 direction;
    Color   color;

    Ball()
        : radius(randf(5, 30)),
          center({randf(radius, BASE_WIDTH - radius), randf(radius, BASE_HEIGHT - radius)}),
          speed(randf(100, 300)), direction({
                                      static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
                                      static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
                                  }),
          color({static_cast<unsigned char>(GetRandomValue(0, 255)),
                 static_cast<unsigned char>(GetRandomValue(0, 255)),
                 static_cast<unsigned char>(GetRandomValue(0, 255)),
                 255}) {}

    void draw(void) const {
        DrawCircleV(center, radius, color);
    }

    void update(const float dt) {
        direction = Vector2Normalize(direction);

        // move
        center.x += direction.x * speed * dt;
        center.y += direction.y * speed * dt;

        // bounds
        if (center.x < radius) {
            center.x = radius;
            direction.x *= -1;
        }

        if (center.x > BASE_WIDTH - radius) {
            center.x = BASE_WIDTH - radius;
            direction.x *= -1;
        }

        if (center.y < radius) {
            center.y = radius;
            direction.y *= -1;
        }

        if (center.y > BASE_HEIGHT - radius) {
            center.y = BASE_HEIGHT - radius;
            direction.y *= -1;
        }
    }
};

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Bouncing Balls");

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    std::array<Ball, MAX_BALLS> balls;

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        for (Ball& ball : balls) {
            ball.update(dt);
        }

        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        for (const Ball& ball : balls) {
            ball.draw();
        }

        EndTextureMode();

        const float scale
            = std::min(static_cast<float>(GetScreenWidth()) / static_cast<float>(BASE_WIDTH),
                       static_cast<float>(GetScreenHeight()) / static_cast<float>(BASE_HEIGHT));

        const Vector2 offset = {(GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
                                (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f};

        const Rectangle source = {0, 0, BASE_WIDTH, -BASE_HEIGHT};
        const Rectangle dest   = {offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, {0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    return 0;
}
