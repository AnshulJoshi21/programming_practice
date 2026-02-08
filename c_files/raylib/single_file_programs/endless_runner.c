#include "utils.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdbool.h>

static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 250;

#define MAX_ENEMIES 10

//-- PLAYER -------------------------------//
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
    assert(player);

    float width  = 20.0f;
    float height = 50.0f;
    float x      = 150.0f;
    float y      = SCREEN_HEIGHT - height;

    player->rect       = (Rectangle){x, y, width, height};
    player->color      = DARKBLUE;
    player->change_y   = 0.0f;
    player->jump_force = -500.0f;
    player->gravity    = 1200.0f;
    player->can_jump   = true;
}

static void player_draw(const Player *player)
{
    assert(player);

    DrawRectangleRec(player->rect, player->color);
}

static void player_update(Player *player, float dt)
{
    assert(player);

    // initiate jump
    if (IsKeyPressed(KEY_W) && player->can_jump) {
        player->can_jump = false;
        player->change_y = player->jump_force;
    }

    // jumping
    player->change_y += player->gravity * dt;
    player->rect.y += player->change_y * dt;

    // hit ground
    if (player->rect.y >= SCREEN_HEIGHT - player->rect.height) {
        player->can_jump = true;
    }

    // bounds
    player->rect.y =
        fmaxf(0.0f, fminf(player->rect.y, SCREEN_HEIGHT - player->rect.height));
}

//-- ENEMY -------------------------------//
typedef struct Enemy
{
    Rectangle rect;
    Color color;
    bool is_scored;

} Enemy;

static void enemy_init(Enemy *enemy)
{
    assert(enemy);

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
    assert(enemy);

    DrawRectangleRec(enemy->rect, enemy->color);
}

static void enemy_update(Enemy *enemy, float dt, float speed)
{
    assert(enemy);

    enemy->rect.x -= speed * dt;
}

//-- ENEMY MANAGER -------------------------------//
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
    assert(em);

    em->list_size       = 0;
    em->horizontal_gap  = SCREEN_WIDTH / 2.0f;
    em->speed           = 200.0f;
    em->speed_increment = 10.0f;
}

static void enemy_manager_draw(const EnemyManager *em)
{
    assert(em);

    for (int i = 0; i < em->list_size; i++) {
        enemy_draw(&em->list[i]);
    }
}

static void enemy_manager_update(EnemyManager *em, float dt, int *score,
                                 float player_x)
{
    assert(em);

    // increment enemy speed
    em->speed += em->speed_increment * dt;

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
        enemy_update(&em->list[i], dt, em->speed);

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

//-- GAME MANAGER -------------------------------//
typedef struct GameManager
{
    int score;
    bool game_over;

    bool show_blinking_text;
    float last_blink_time;
    float blink_interval;

    Player player;
    EnemyManager em;

} GameManager;

static void gm_reset(GameManager *gm)
{
    assert(gm);

    gm->score     = 0;
    gm->game_over = false;

    gm->show_blinking_text = false;
    gm->last_blink_time    = GetTime();
    gm->blink_interval     = 1.0f;

    player_init(&gm->player);
    enemy_manager_init(&gm->em);
}

static void gm_init(GameManager *gm)
{
    assert(gm);

    gm->score     = 0;
    gm->game_over = false;

    gm->show_blinking_text = false;
    gm->last_blink_time    = 0.0f;
    gm->blink_interval     = 1.0f;

    player_init(&gm->player);
    enemy_manager_init(&gm->em);
}

static void gm_draw(const GameManager *gm)
{
    assert(gm);

    // score
    DrawText(TextFormat("%d", gm->score), 20, 20, 30, BLACK);

    player_draw(&gm->player);
    enemy_manager_draw(&gm->em);

    if (gm->game_over) {
        center_and_draw_text(
            "GAME OVER", 30.0f, 20.0f,
            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 100}, BLACK);

        if (gm->show_blinking_text) {
            center_and_draw_text(
                "Press [ENTER] to restart", 20.0f, 2.0f,
                (Rectangle){1, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 100}, BLACK);
        }
    }
}

static void gm_update(GameManager *gm, float dt)
{
    assert(gm);

    if (!gm->game_over) {

        player_update(&gm->player, dt);
        enemy_manager_update(&gm->em, dt, &gm->score, gm->player.rect.x);

        // player collision enemy
        for (int i = 0; i < gm->em.list_size; i++) {
            if (CheckCollisionRecs(gm->player.rect, gm->em.list[i].rect)) {
                gm->game_over = true;
            }
        }
    } else {
        // show blinking text
        float current_time = GetTime();
        if (current_time - gm->last_blink_time >= gm->blink_interval) {
            gm->last_blink_time = current_time;

            gm->show_blinking_text = !gm->show_blinking_text;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            gm->game_over = false;
            gm->score     = 0;

            player_init(&gm->player);
            enemy_manager_init(&gm->em);
        }
    }
}

//-- MAIN -------------------------------//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless Runner");

    GameManager gm;
    gm_init(&gm);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        gm_update(&gm, dt);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        gm_draw(&gm);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
