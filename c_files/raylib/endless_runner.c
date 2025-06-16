#include <raylib.h>

#define ENEMIES_LENGTH 10

// PLAYER
typedef struct Player
{
  Rectangle rect;
  Color color;
  float change_y;
  float gravity;
  float jump_force;
  bool is_jumping;

} Player;

void
player_init(Player* player)
{
  float height = 50.0f;
  player->rect = (Rectangle){ 100, GetScreenHeight() - height, 20, height };
  player->color = RED;
  player->change_y = 0.0f;
  player->gravity = 1500.0f;
  player->jump_force = -550.0f;
  player->is_jumping = false;
}

void
player_draw(Player* player)
{
  DrawRectangleRec(player->rect, player->color);
}

void
player_update(Player* player)
{
  if (IsKeyPressed(KEY_UP) && !player->is_jumping) {
    player->is_jumping = true;
    player->change_y = player->jump_force;
  }

  if (player->is_jumping) {
    player->change_y += player->gravity * GetFrameTime();
    player->rect.y += player->change_y * GetFrameTime();
  }

  float ground_level = GetScreenHeight() - player->rect.height;

  if (player->rect.y >= ground_level) {
    player->rect.y = ground_level;
    player->change_y = 0.0f;
    player->is_jumping = false;
  }
}

// ENEMY
typedef struct Enemy
{
  Rectangle rect;
  Color color;
  float speed;
  float horizontal_distance;
  bool scored;

} Enemy;

void
enemy_init(Enemy* enemy)
{
  float width = GetRandomValue(20, 40);
  float height = GetRandomValue(40, 70);
  enemy->rect =
    (Rectangle){ GetScreenWidth(), GetScreenHeight() - height, width, height };
  enemy->color = DARKGREEN;
  enemy->speed = 300.0f;
  enemy->horizontal_distance = GetRandomValue(200, 300);
  enemy->scored = false;
}

void
enemy_draw(Enemy* enemy)
{
  DrawRectangleRec(enemy->rect, enemy->color);
}

void
enemy_update(Enemy* enemy)
{
  enemy->rect.x -= enemy->speed * GetFrameTime();
}

// ENEMIES
typedef struct Enemies
{
  Enemy list[ENEMIES_LENGTH];
  int size;

} Enemies;

void
enemies_init(Enemies* enemies)
{
  Enemy enemy;
  enemy_init(&enemy);
  enemies->list[0] = enemy;
  enemies->size = 1;
}

void
enemies_draw(Enemies* enemies)
{
  for (int i = 0; i < enemies->size; i++) {
    enemy_draw(&enemies->list[i]);
  }
}

void
enemies_update(Enemies* enemies,
               int* score,
               bool* game_over,
               Rectangle player_rect)
{
  // add enemy to list if necessary
  Enemy last_enemy = enemies->list[enemies->size - 1];
  if (enemies->size <= 0 ||
      last_enemy.rect.x < GetScreenWidth() - last_enemy.horizontal_distance) {

    Enemy enemy;
    enemy_init(&enemy);
    enemies->list[enemies->size] = enemy;
    enemies->size += 1;
  }

  // move enemy
  for (int i = 0; i < enemies->size; i++) {
    enemy_update(&enemies->list[i]);

    // check game_over condition
    if (CheckCollisionRecs(enemies->list[i].rect, player_rect)) {
      *game_over = true;
      return;
    }

    // update score
    if (player_rect.x > enemies->list[i].rect.x + enemies->list[i].rect.width &&
        !enemies->list[i].scored) {

      *score += 1;
      enemies->list[i].scored = true;
    }

    // remove enemy from list
    if (enemies->list[i].rect.x < -(enemies->list[i].rect.width * 2)) {
      for (int j = i; j < enemies->size; j++) {
        enemies->list[j] = enemies->list[j + 1];
      }
      Enemy empty_enemy = { 0 };
      enemies->list[enemies->size] = empty_enemy;
      enemies->size -= 1;

      // reset current index position
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
  const int SCREEN_HEIGHT = 250;
  const char SCREEN_TITLE[] = "Endless Runner";
  const Color SCREEN_BACKGROUND = SKYBLUE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  // INIT
  int score = 0;
  bool game_over = false;

  bool show_text = false;
  float last_time = 0.0f;
  float blink_interval = 1.0f;

  Enemies enemies;
  Player player;

  player_init(&player);
  enemies_init(&enemies);

  while (!WindowShouldClose()) {
    // UPDATES
    // blink game over text
    if (game_over) {
      float current_time = GetTime();
      if (current_time - last_time >= blink_interval) {
        show_text = !show_text;
        last_time = current_time;
      }
    }

    if (!game_over) {
      player_update(&player);
      enemies_update(&enemies, &score, &game_over, player.rect);
    } else {
      if (IsKeyPressed(KEY_ENTER)) {
        score = 0;
        game_over = false;
        show_text = false;
        last_time = 0.0f;

        player_init(&player);
        enemies_init(&enemies);
      }
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    // DRAW
    DrawText(TextFormat("Score: %d", score), 20, 10, 30, BLACK);

    if (!game_over) {
      player_draw(&player);
      enemies_draw(&enemies);
    } else if (game_over) {
      center_and_draw_text(
        "GAME OVER", 40, 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

      if (show_text) {
        center_and_draw_text("press ENTER to restart",
                             30,
                             0,
                             0,
                             GetScreenWidth(),
                             GetScreenHeight() + 100,
                             BLACK);
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}