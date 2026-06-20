#include <algorithm>
#include <array>
#include <assert.h>
#include <random>
#include <raylib.h>

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
    Vector2 velocity;
    Color   color;

    Ball()
        : radius(randf(5, 30)),
          center({randf(radius, BASE_WIDTH - radius), randf(radius, BASE_HEIGHT - radius)}),
          color({static_cast<unsigned char>(GetRandomValue(0, 255)),
                 static_cast<unsigned char>(GetRandomValue(0, 255)),
                 static_cast<unsigned char>(GetRandomValue(0, 255)),
                 255}) {
        const float speed = randf(100, 300);
        const float angle = randf(0, 2 * PI);

        velocity = {std::cos(angle) * speed, std::sin(angle) * speed};
    }

    void draw(void) const {
        DrawCircleV(center, radius, color);
    }

    void update(const float dt) {
        // move
        center.x += velocity.x * dt;
        center.y += velocity.y * dt;

        // bounds
        if (center.x < radius) {
            center.x = radius;
            velocity.x *= -1;
        }

        if (center.x > BASE_WIDTH - radius) {
            center.x = BASE_WIDTH - radius;
            velocity.x *= -1;
        }

        if (center.y < radius) {
            center.y = radius;
            velocity.y *= -1;
        }

        if (center.y > BASE_HEIGHT - radius) {
            center.y = BASE_HEIGHT - radius;
            velocity.y *= -1;
        }
    }
};

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Bouncing Balls v2");

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
