#include "utils.h"

#include <math.h>
#include <raylib.h>
#include <stdbool.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 250;
static const char *SCREEN_TITLE      = "Endless Runner";
static const Color SCREEN_BACKGROUND = SKYBLUE;

#define MAX_ENEMIES 10

//************************************************//
// PLAYER
//************************************************//
typedef struct Player
{
    Rectangle rect;
    Color color;
    float change_y;
    float jump_force;
    float gravity;
    bool can_jump;

} Player;

static void player_init(Player *player)
{
    if (!player)
        return;

    float width  = 20.0f;
    float height = 50.0f;
    float x      = 150.0f;
    float y      = SCREEN_HEIGHT - height;

    player->rect       = (Rectangle){x, y, width, height};
    player->color      = BLUE;
    player->change_y   = 0.0f;
    player->jump_force = -500.0f;
    player->gravity    = 1200.0f;
    player->can_jump   = true;
}

static void player_draw(const Player *player)
{
    if (!player)
        return;

    DrawRectangleRec(player->rect, player->color);
}

static void player_update(Player *player, float delta_time)
{
    if (!player)
        return;

    // initiate jump
    if (IsKeyPressed(KEY_W) && player->can_jump) {
        player->can_jump = false;
        player->change_y = player->jump_force;
    }

    // jumping
    player->change_y += player->gravity * delta_time;
    player->rect.y += player->change_y * delta_time;

    // hit ground
    if (player->rect.y >= SCREEN_HEIGHT - player->rect.height) {
        player->can_jump = true;
    }

    // bounds
    player->rect.y =
        fmaxf(0.0f, fminf(player->rect.y, SCREEN_HEIGHT - player->rect.height));
}

//*********************************************//
// ENEMIES
//************************************************//
typedef struct Enemy
{
    Rectangle rect;
    Color color;
    bool is_scored;

} Enemy;

static void enemy_init(Enemy *enemy)
{
    if (!enemy)
        return;

    float width  = 20.0f;
    float height = GetRandomValue(30, 70);
    float x      = SCREEN_WIDTH;
    float y      = SCREEN_HEIGHT - height;

    enemy->rect      = (Rectangle){x, y, width, height};
    enemy->color     = DARKGREEN;
    enemy->is_scored = false;
}

static void enemy_draw(const Enemy *enemy)
{
    if (!enemy)
        return;

    DrawRectangleRec(enemy->rect, enemy->color);
}

static void enemy_update(Enemy *enemy, float delta_time, float speed)
{
    if (!enemy)
        return;

    enemy->rect.x -= speed * delta_time;
}

// ENEMY MANAGER
typedef struct EnemyManager
{
    Enemy list[MAX_ENEMIES];
    int list_size;
    float horizontal_gap;
    float speed;
    float speed_increment;

} EnemyManager;

static void enemy_manager_init(EnemyManager *em)
{
    if (!em)
        return;

    em->list_size       = 0;
    em->horizontal_gap  = SCREEN_WIDTH / 2.0f;
    em->speed           = 200.0f;
    em->speed_increment = 10.0f;
}

static void enemy_manager_draw(const EnemyManager *em)
{
    if (!em)
        return;

    for (int i = 0; i < em->list_size; i++) {
        enemy_draw(&em->list[i]);
    }
}

static void enemy_manager_update(EnemyManager *em, float delta_time, int *score,
                                 float player_x)
{
    if (!em)
        return;

    // increment enemy speed
    em->speed += em->speed_increment * delta_time;

    // add enemy to list
    if (em->list_size < MAX_ENEMIES) {
        bool can_spawn = false;
        if (em->list_size <= 0) {
            can_spawn = true;
        } else {
            Enemy *last_enemy = &em->list[em->list_size - 1];
            if (last_enemy->rect.x + last_enemy->rect.width +
                    em->horizontal_gap <=
                SCREEN_WIDTH) {
                can_spawn = true;
            }
        }

        if (can_spawn) {
            enemy_init(&em->list[em->list_size]);
            em->list_size++;
        }
    }

    // update enemy
    for (int i = 0; i < em->list_size; i++) {
        enemy_update(&em->list[i], delta_time, em->speed);

        // update score
        if (!em->list[i].is_scored) {
            if (player_x >= em->list[i].rect.x + em->list[i].rect.width) {
                em->list[i].is_scored = true;
                *score += 1;
            }
        }
        // remove offscreen enemy
        if (em->list[i].rect.x + em->list[i].rect.width <= 0) {
            for (int j = i; j < em->list_size; j++) {
                em->list[j] = em->list[j + 1];
            }
            em->list_size--;
            i--;
        }
    }
}

//*********************************************//
// MAIN
//************************************************//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    int score      = 0;
    bool game_over = false;

    bool show_blinking_text = false;
    float last_blink_time   = 0.0f;
    float blink_interval    = 1.0f;

    Player player;
    player_init(&player);

    EnemyManager em;
    enemy_manager_init(&em);

    while (!WindowShouldClose()) {
        // 2.UPDATE
        // game running
        if (!game_over) {
            float delta_time = GetFrameTime();

            player_update(&player, delta_time);
            enemy_manager_update(&em, delta_time, &score, player.rect.x);

            // player collision enemy
            for (int i = 0; i < em.list_size; i++) {
                if (CheckCollisionRecs(player.rect, em.list[i].rect)) {
                    game_over = true;
                }
            }
        } else {
            // show blinking text
            float current_time = GetTime();
            if (current_time - last_blink_time >= blink_interval) {
                last_blink_time = current_time;

                show_blinking_text = !show_blinking_text;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                game_over = false;
                score     = 0;

                player_init(&player);
                enemy_manager_init(&em);
            }
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        // score
        DrawText(TextFormat("%d", score), 20, 20, 30, BLACK);

        player_draw(&player);
        enemy_manager_draw(&em);

        if (game_over) {
            center_and_draw_text(
                "GAME OVER", 30.0f, 20.0f,
                (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 100}, BLACK);

            if (show_blinking_text) {
                center_and_draw_text(
                    "Press [ENTER] to restart", 20.0f, 2.0f,
                    (Rectangle){1, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 100},
                    BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
