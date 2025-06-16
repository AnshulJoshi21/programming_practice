#include "utils.h"
#include <raylib.h>

#define PILLARS_LENGTH 10

// PLAYER
typedef struct Player
{
  Rectangle rect;
  Color color;
  float change_y;
  float gravity;
  float jump_force;
  bool active;

} Player;

void
player_init(Player* player)
{
  player->rect = (Rectangle){ 200, 200, 30, 30 };
  player->color = RED;
  player->change_y = 0.0f;
  player->gravity = 1500.0f;
  player->jump_force = -600.0f;
  player->active = false;
}

void
player_draw(Player* player)
{
  DrawRectangleRec(player->rect, player->color);
}

void
player_update(Player* player)
{
  if (IsKeyPressed(KEY_UP)) {
    player->change_y = player->jump_force;
    player->active = true;
  }

  if (player->active) {
    player->change_y += player->gravity * GetFrameTime();
    player->rect.y += player->change_y * GetFrameTime();
  }

  player->rect.y = max_float(
    0.0f, min_float(player->rect.y, GetScreenHeight() - player->rect.height));
}

// Pillar
typedef struct Pillar
{
  Rectangle rect;
  Color color;
  float speed;
  float horizontal_distance;
  float vertical_distance;
  bool scored;

} Pillar;

void
pillar_init(Pillar* pillar)
{
  pillar->horizontal_distance = 300.0f;
  pillar->vertical_distance = 200.0f;
  float height =
    GetRandomValue(0, GetScreenHeight() - pillar->vertical_distance);
  pillar->rect = (Rectangle){ GetScreenWidth(), 0, 100.0f, height };
  pillar->color = DARKGREEN;
  pillar->speed = 300.0f;
  pillar->scored = false;
}

void
pillar_draw(Pillar* pillar)
{
  // top pillar
  DrawRectangleRec(pillar->rect, pillar->color);

  // bottom pillar
  DrawRectangleRec((Rectangle){ pillar->rect.x,
                                pillar->rect.height + pillar->vertical_distance,
                                pillar->rect.width,
                                GetScreenHeight() - pillar->rect.height },
                   pillar->color);
}

void
pillar_update(Pillar* pillar)
{
  pillar->rect.x -= pillar->speed * GetFrameTime();
}

// PILLARS
typedef struct Pillars
{
  Pillar list[PILLARS_LENGTH];
  int size;

} Pillars;

void
pillars_init(Pillars* pillars)
{
  Pillar pillar;
  pillar_init(&pillar);

  pillars->list[0] = pillar;
  pillars->size = 1;
}

void
pillars_draw(Pillars* pillars)
{
  for (int i = 0; i < pillars->size; i++) {
    pillar_draw(&pillars->list[i]);
  }
}

void
pillars_update(Pillars* pillars,
               int* score,
               bool* game_over,
               Rectangle player_rect)
{
  // add pillar if necessary
  Pillar current_pillar = pillars->list[pillars->size - 1];
  if (pillars->size <= 0 ||
      current_pillar.rect.x < GetScreenWidth() -
                                current_pillar.horizontal_distance -
                                current_pillar.rect.width) {
    Pillar pillar;
    pillar_init(&pillar);
    pillars->list[pillars->size] = pillar;
    pillars->size++;
  }

  for (int i = 0; i < pillars->size; i++) {
    // move pillar
    pillar_update(&pillars->list[i]);

    // game over condition - player collision pillar
    // top pillar collision check
    if (CheckCollisionRecs(pillars->list[i].rect, player_rect)) {
      
      *game_over = true;
      return;
    }
    // bottom pillar collision check
    if (CheckCollisionRecs(
          (Rectangle){ pillars->list[i].rect.x,
                       pillars->list[i].rect.height +
                         pillars->list[i].vertical_distance,
                       pillars->list[i].rect.width,
                       GetScreenHeight() - pillars->list[i].rect.height },
          player_rect)) {
            
      *game_over = true;
      return;
    }

    // update score
    if (player_rect.x > pillars->list[i].rect.x + pillars->list[i].rect.width &&
        !pillars->list[i].scored) {

      *score += 1;
      pillars->list[i].scored = true;
    }

    // remove pillar
    if (pillars->list[i].rect.x < -(pillars->list[i].rect.width * 2)) {
      for (int j = i; j < pillars->size; j++) {
        pillars->list[j] = pillars->list[j + 1];
      }
      Pillar empty_pillar = { 0 };
      pillars->list[pillars->size] = empty_pillar;
      pillars->size--;

      // resize main index
      i--;
    }
  }
}

// UTILITY FUNCTIONS
void
center_and_draw_text(char* text,
                     int font_size,
                     int rect_x,
                     int rect_y,
                     int rect_width,
                     int rect_height,
                     Color color)
{
  int text_width = MeasureText(text, font_size);
  int text_x = rect_x + rect_width / 2 - text_width / 2;
  int text_y = rect_y + rect_height / 2 - font_size / 2;

  DrawText(text, text_x, text_y, font_size, color);
}

// MAIN
int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "Flappy Bird";
  const Color SCREEN_BACKGROUND = SKYBLUE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  // INIT
  int score = 0;
  bool game_over = false;

  bool show_text = false;
  float last_time = 0.0f;
  float blink_interval = 1.0f;

  Player player;
  Pillars pillars;

  player_init(&player);
  pillars_init(&pillars);

  while (!WindowShouldClose()) {
    // UPDATE
    if (game_over) {
      float current_time = GetTime();
      if (current_time - last_time >= blink_interval) {
        show_text = !show_text;
        last_time = current_time;
      }
    }

    if (!game_over) {
      player_update(&player);
      pillars_update(&pillars, &score, &game_over, player.rect);

    } else if (game_over) {
      if (IsKeyPressed(KEY_ENTER)) {
        score = 0;
        game_over = false;
        show_text = false;
        last_time = 0.0f;

        player_init(&player);
        pillars_init(&pillars);
      }
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    // DRAW
    if (!game_over) {
      player_draw(&player);
      pillars_draw(&pillars);
    } else if (game_over) {
      center_and_draw_text(
        "GAME OVER", 40, 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

      if (show_text) {
        center_and_draw_text("press ENTER to restart",
                             30,
                             0,
                             0,
                             GetScreenWidth(),
                             GetScreenHeight() + 300,
                             BLACK);
      }
    }

    DrawText(TextFormat("Score: %d", score), 20, 20, 30, BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}