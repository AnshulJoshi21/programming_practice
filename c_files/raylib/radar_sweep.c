#include <math.h>
#include <raylib.h>

typedef struct Ring
{
  Vector2 center;
  float inner_radius;
  float outer_radius;
  float start_angle;
  float end_angle;
  int segments;
  Color color;

} Ring;

void
ring_init(Ring* ring)
{
  ring->center = (Vector2){ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
  ring->inner_radius = 250.0f;
  ring->outer_radius = 260.0f;
  ring->start_angle = 0.0f;
  ring->end_angle = 360.0f;
  ring->segments = 64;
  ring->color = BLACK;
}

void
ring_draw(Ring* ring)
{
  DrawRing(ring->center,
           ring->inner_radius,
           ring->outer_radius,
           ring->start_angle,
           ring->end_angle,
           ring->segments,
           ring->color);
}

typedef struct Line
{
  Vector2 start_pos;
  Vector2 end_pos;
  float thickness;
  Color color;

} Line;

void
line_init(Line* line, Ring* ring)
{
  line->start_pos = ring->center;
  line->end_pos = (Vector2){ 0, 0 };
  line->thickness = 10.0f;
  line->color = RED;
}

void
line_draw(Line* line)
{
  DrawLineEx(line->start_pos, line->end_pos, line->thickness, line->color);
}

int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "Radar Sweep";
  const Color SCREEN_BACKGROUND = RAYWHITE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  float angle = 0.0f;
  float speed = 50.0f;

  Ring ring;
  Line line;

  ring_init(&ring);
  line_init(&line, &ring);

  while (!WindowShouldClose()) {

    angle += speed * GetFrameTime();
    if (angle >= 360.0f) {
      angle = 0.0f;
    }

    float angle_radians = angle * DEG2RAD;

    line.end_pos.x = cosf(angle_radians) * ring.inner_radius + ring.center.x;
    line.end_pos.y = sinf(angle_radians) * ring.inner_radius + ring.center.y;

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);
    
    ring_draw(&ring);
    line_draw(&line);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}