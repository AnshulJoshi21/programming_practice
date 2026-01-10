#include "utils.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Flappy Bird";
static const Color SCREEN_BACKGROUND = RAYWHITE;

#define MAX_PILLARS 5
#define PILLAR_SPAWN_OFFSET 10.0f

//---- PLAYER -------------------------------//
typedef struct Player
{
    Rectangle rect;
    Color color;
    float change_y;
    float jump_force;
    float gravity;

} Player;

static void player_init(Player *player)
{
    assert(player);

    float size      = 40.0f;
    float start_pos = 250.0f;

    player->rect       = (Rectangle){start_pos, start_pos, size, size};
    player->color      = BLUE;
    player->change_y   = 0.0f;
    player->jump_force = -550.0f;
    player->gravity    = 1500.0f;
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
    if (IsKeyPressed(KEY_W)) {
        player->change_y = player->jump_force;
    }

    // jumping
    player->change_y += player->gravity * dt;
    player->rect.y += player->change_y * dt;

    // bounds
    player->rect.y =
        fmaxf(0.0f, fminf(player->rect.y, SCREEN_HEIGHT - player->rect.height));
}

//---- PILLAR -------------------------------//
typedef struct Pillar
{
    Rectangle rect;
    Color color;
    float is_scored;

} Pillar;

static void pillar_init(Pillar *pillar, float vertical_gap)
{
    assert(pillar);

    float width  = 100.0f;
    float height = random_uniform(0.0f, SCREEN_HEIGHT - vertical_gap);
    float x      = SCREEN_WIDTH + PILLAR_SPAWN_OFFSET;
    float y      = 0.0f;

    pillar->rect      = (Rectangle){x, y, width, height};
    pillar->color     = DARKGREEN;
    pillar->is_scored = false;
}

static Rectangle get_bottom_pillar(const Pillar *pillar, float vertical_gap)
{
    assert(pillar);

    float bottom_y      = pillar->rect.height + vertical_gap;
    float bottom_height = SCREEN_HEIGHT - bottom_y;

    return (Rectangle){pillar->rect.x, bottom_y, pillar->rect.width,
                       bottom_height};
}

static void pillar_draw(const Pillar *pillar, float vertical_gap)
{
    assert(pillar);

    // top pillar
    DrawRectangleRec(pillar->rect, pillar->color);

    // bottom pillar
    Rectangle bottom_pillar = get_bottom_pillar(pillar, vertical_gap);
    DrawRectangleRec(bottom_pillar, pillar->color);
}

static void pillar_update(Pillar *pillar, float dt, float speed)
{
    assert(pillar);

    // move
    pillar->rect.x -= speed * dt;
}

//---- PILLAR_MANAGER -------------------------------//
typedef struct PillarManager
{
    Pillar list[MAX_PILLARS];
    int list_size;
    float speed;
    float speed_increment;
    float vertical_gap;
    float horizontal_gap;

} PillarManager;

static void pm_init(PillarManager *pm)
{
    assert(pm);

    pm->list_size       = 0;
    pm->speed           = 200.0f;
    pm->speed_increment = 10.0f;
    pm->vertical_gap    = 200.0f;
    pm->horizontal_gap  = SCREEN_WIDTH / 2.0f;
}

static void pm_draw(const PillarManager *pm)
{
    assert(pm);

    for (int i = 0; i < pm->list_size; i++) {
        pillar_draw(&pm->list[i], pm->vertical_gap);
    }
}

static void pm_update(PillarManager *pm, float dt, int *score, float player_x)
{
    assert(pm);
    assert(score);

    // speed increment
    pm->speed += pm->speed_increment * dt;

    // add pillar to list
    if (pm->list_size < MAX_PILLARS) {
        bool can_spawn = false;

        if (pm->list_size <= 0) {
            can_spawn = true;
        } else {
            Pillar *last_pillar = &pm->list[pm->list_size - 1];
            assert(last_pillar);

            if (last_pillar->rect.x + last_pillar->rect.width +
                    pm->horizontal_gap <=
                SCREEN_WIDTH) {

                can_spawn = true;
            }
        }

        if (can_spawn) {
            pillar_init(&pm->list[pm->list_size], pm->vertical_gap);
            pm->list_size++;
        }
    }

    // update pillar
    for (int i = 0; i < pm->list_size; i++) {
        pillar_update(&pm->list[i], dt, pm->speed);

        // update score
        if (!pm->list[i].is_scored) {
            if (player_x >= pm->list[i].rect.x + pm->list[i].rect.width) {
                pm->list[i].is_scored = true;
                *score += 1;
            }
        }
        // remove offscreen pillar
        if (pm->list[i].rect.x + pm->list[i].rect.width + PILLAR_SPAWN_OFFSET <=
            0) {
            for (int j = i; j < pm->list_size; j++) {
                pm->list[j] = pm->list[j + 1];
            }
            pm->list_size--;
            i--;
        }
    }
}

//---- MAIN -------------------------------//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    int score       = 0;
    bool game_over  = false;
    bool game_start = false;

    bool show_blinking_text = false;
    Timer interval_timer;
    interval_timer_init(&interval_timer, 1.0f);

    Player player;
    player_init(&player);

    PillarManager pm;
    pm_init(&pm);

    while (!WindowShouldClose()) {
        // 2.UPDATE

        // blinking text update
        if (game_over || !game_start) {
            if (interval_timer_update(&interval_timer)) {
                show_blinking_text = !show_blinking_text;
            }
        }

        // activate game
        if (IsKeyPressed(KEY_W)) {
            game_start = true;
        }

        // game running
        if (!game_over && game_start) {
            float dt = GetFrameTime();

            player_update(&player, dt);
            pm_update(&pm, dt, &score, player.rect.x);

            // game over conditions
            // 1. player hits ground
            if (player.rect.y + player.rect.height >= SCREEN_HEIGHT) {
                game_over = true;
            }
            // 2. player collision pillars
            for (int i = 0; i < pm.list_size; i++) {
                // top pillar
                if (CheckCollisionRecs(player.rect, pm.list[i].rect)) {
                    game_over = true;
                }

                // bottom pillar
                Rectangle bottom_pillar =
                    get_bottom_pillar(&pm.list[i], pm.vertical_gap);

                if (CheckCollisionRecs(player.rect, bottom_pillar)) {
                    game_over = true;
                }
            }

        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                score      = 0;
                game_over  = false;
                game_start = false;

                player_init(&player);
                pm_init(&pm);
            }
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        player_draw(&player);
        pm_draw(&pm);

        // draw score
        DrawText(TextFormat("%d", score), 50.0f, 50.0f, 30.0f, BLACK);

        if (!game_start) {
            if (show_blinking_text) {
                center_and_draw_text(
                    "Press [W] to begin", 20.0f, 2.0f,
                    (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200},
                    BLACK);
            }
        }

        if (game_over) {
            float width     = 300.0f;
            float height    = 150.0f;
            float x         = SCREEN_WIDTH / 2.0f - width / 2.0f;
            float y         = SCREEN_HEIGHT / 2.0f - height / 2.0f;
            Rectangle rect  = (Rectangle){x, y, width, height};
            Color color     = BLACK;
            float thickness = 5.0f;

            // draw outline rect
            DrawRectangleLinesEx(rect, thickness, color);

            // draw centered text
            center_and_draw_text("GAME OVER", 40.0f, 2.0f, rect, color);

            // draw blinking text
            if (show_blinking_text) {
                center_and_draw_text(
                    "Press [ENTER] to restart", 20.0f, 2.0f,
                    (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200},
                    color);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
