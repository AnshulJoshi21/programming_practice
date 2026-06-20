#include <algorithm>
#include <assert.h>
#include <raylib.h>
#include <raymath.h>

const int   BASE_WIDTH    = 800;
const int   BASE_HEIGHT   = 600;
const float PADDLE_WIDTH  = 15.0f;
const float PADDLE_HEIGHT = 100.0f;

class Ball {
  public:
    float   radius;
    Vector2 center;
    float   speed;
    float   speed_increment;
    Vector2 direction;
    Color   color;
    bool    active;

    void reset(void) {
        center    = {BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f};
        speed     = 300.0f;
        direction = {static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
                     static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1)};
        active    = false;
    }

    Ball() : radius(10.0f), speed_increment(10.0f), color(RED) {
        reset();
    }

    void draw(void) const {
        DrawCircleV(center, radius, color);
    }

    void update(const float dt) {
        if (IsKeyPressed(KEY_SPACE)) {
            active = true;
        }

        if (active) {
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
    }
};

class Paddle {
  public:
    Rectangle rect;
    float     speed;
    Color     color;
    float     roundness;
    int       segments;

    void reset(void) {
        rect.y = BASE_HEIGHT / 2.0f - rect.height / 2.0f;
    }

    Paddle(const float x)
        : rect({x, 0, PADDLE_WIDTH, PADDLE_HEIGHT}), speed(300.0f), color(BLACK), roundness(0.90f),
          segments(0) {
        //
        reset();
    }

    void draw(void) const {
        DrawRectangleRounded(rect, roundness, segments, color);
    }

    void update_player(const float dt) {
        if (IsKeyDown(KEY_W) && rect.y > 0) {
            rect.y -= speed * dt;
        }
        if (IsKeyDown(KEY_S) && rect.y < BASE_HEIGHT - rect.height) {
            rect.y += speed * dt;
        }
    }

    void update_ai(const float dt, const float ball_y) {
        if (ball_y < rect.y + rect.height / 2.0f && rect.y > 0) {
            rect.y -= speed * dt;
        }
        if (ball_y > rect.y + rect.height / 2.0f && rect.y < BASE_HEIGHT - rect.height) {
            rect.y += speed * dt;
        }
    }
};

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Pong");

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    Ball ball;

    Paddle player(10.0f);
    Paddle ai(BASE_WIDTH - player.rect.width - 10.0f);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        ball.update(dt);
        player.update_player(dt);
        ai.update_ai(dt, ball.center.y);

        BeginTextureMode(canvas);
        ClearBackground(LIGHTGRAY);

        ball.draw();
        player.draw();
        ai.draw();

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
