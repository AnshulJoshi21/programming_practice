#include <math.h>
#include <raylib.h>

#define NUM_OF_SNOWFLAKES 200

typedef struct Snowflake {
  Vector2 position;
  float radius;
  float fall_speed;
  float drift_speed;
  float drift_angle;
  float drift_frequency;
  float drift_amplitude;
  Color color;

} Snowflake;

void snowflake_init(Snowflake *snowflake) {
  snowflake->radius = GetRandomValue(1, 4);
  snowflake->position.x =
      GetRandomValue(snowflake->radius, GetScreenWidth() - snowflake->radius);
  snowflake->position.y =
      GetRandomValue(-GetScreenHeight(), -snowflake->radius);
  snowflake->fall_speed = GetRandomValue(20, 100) / 100.0f * 60.0f;
  snowflake->drift_speed = GetRandomValue(5, 30) / 100.0f;
  snowflake->drift_frequency = GetRandomValue(1, 5) / 10.0f;
  snowflake->drift_amplitude = GetRandomValue(10, 50);
  snowflake->drift_angle = GetRandomValue(0, 360) * DEG2RAD;
  snowflake->color = LIGHTGRAY;
}

void snowflake_draw(Snowflake *snowflake) {
  DrawCircleV(snowflake->position, snowflake->radius, snowflake->color);
}

void snowflake_update(Snowflake *snowflake) {
  float time = GetTime();

  snowflake->position.y += snowflake->fall_speed * GetFrameTime();

  snowflake->position.x +=
      (sinf(time * snowflake->drift_frequency + snowflake->drift_angle) *
       snowflake->drift_amplitude * snowflake->drift_speed * GetFrameTime());

  if (snowflake->position.y > GetScreenHeight() + snowflake->radius) {
    snowflake_init(snowflake);
  }
}

int main(void) {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "Falling Snow";
  const Color SCREEN_BACKGROUND = BLACK;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  Snowflake snowflakes[NUM_OF_SNOWFLAKES];

  for (int i = 0; i < NUM_OF_SNOWFLAKES; i++) {
    Snowflake snowflake;
    snowflake_init(&snowflake);

    snowflakes[i] = snowflake;
  }

  while (!WindowShouldClose()) {

    for (int i = 0; i < NUM_OF_SNOWFLAKES; i++) {
      snowflake_update(&snowflakes[i]);
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    for (int i = 0; i < NUM_OF_SNOWFLAKES; i++) {
      snowflake_draw(&snowflakes[i]);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
