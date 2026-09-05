#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 200;

static const float JUMP_FORCE = 500;
static const float GRAVITY    = 1200;

#define MAX_ENEMIES 10

static inline float randf(const float min, const float max) {
    if (min == max) return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float) rand() / (float) RAND_MAX) * (maximum - minimum);
}

static void draw_centered_text(const char* text, const Rectangle bounds, const float font_size) {
    assert(text);

    const Font    font      = GetFontDefault();
    const float   spacing   = 2.0f;
    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    const Vector2 pos       = (Vector2){
        bounds.x + (bounds.width - text_size.x) / 2.0f,
        bounds.y + (bounds.height - text_size.y) / 2.0f,
    };
    const Color tint = BLACK;

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}

typedef struct {
    Rectangle rect;
    Color     color;
    float     change_y;
    bool      can_jump;
} Player;

static void player_init(Player* player) {
    assert(player);

    const float width  = 20.0f;
    const float height = 50.0f;
    player->rect       = (Rectangle){200.0f, GetScreenHeight() - height, width, height};
    player->color      = DARKBLUE;
    player->change_y   = 0.0f;
    player->can_jump   = true;
}

static void player_update(Player* player, const float dt) {
    assert(player);

    // initiate jump
    if (IsKeyPressed(KEY_W) && player->can_jump) {
        player->can_jump = false;
        player->change_y = -JUMP_FORCE;
    }

    player->change_y += GRAVITY * dt;
    player->rect.y += player->change_y * dt;

    if (player->rect.y + player->rect.height >= GetScreenHeight()) {
        player->change_y = 0.0f;
        player->can_jump = true;
    }

    player->rect.y = fmaxf(0, fminf(player->rect.y, GetScreenHeight() - player->rect.height));
}

static void player_draw(const Player* player) {
    assert(player);

    DrawRectangleRec(player->rect, player->color);
}

typedef struct {
    Rectangle rect;
    Color     color;
    bool      is_scored;
} Enemy;

static void enemy_init(Enemy* enemy) {
    assert(enemy);

    const float width  = 20;
    const float height = randf(30, 70);
    enemy->rect        = (Rectangle){GetScreenWidth(), GetScreenHeight() - height, width, height};
    enemy->color       = DARKGREEN;
    enemy->is_scored   = false;
}

typedef struct {
    Enemy enemies[MAX_ENEMIES];
    int   size;
    float horizontal_gap;
    float speed;
    float speed_increment;
} EnemyManager;

static void em_init(EnemyManager* em) {
    assert(em);

    em->size            = 0;
    em->horizontal_gap  = GetScreenWidth() / 2.0f;
    em->speed           = 100.0f;
    em->speed_increment = 10.0f;
}

static void em_update(EnemyManager* em, const float dt) {
    assert(em);

    em->speed += em->speed_increment * dt;

    // spawn
    if (em->size < MAX_ENEMIES) {
        const Enemy* last_enemy = &em->enemies[em->size - 1];
        if (em->size == 0
            || last_enemy->rect.x + last_enemy->rect.width + em->horizontal_gap
                   < GetScreenWidth()) {
            //
            enemy_init(&em->enemies[em->size]);
            em->size++;
        }
    }

    // update enemies
    for (int i = 0; i < em->size; i++) {
        Enemy* enemy = &em->enemies[i];

        // move
        enemy->rect.x -= em->speed * dt;

        // despawn
        if (enemy->rect.x + (enemy->rect.width * 2) < 0) {
            em->enemies[i] = em->enemies[--em->size];
            i--;
        }
    }
}

static void em_draw(const EnemyManager* em) {
    assert(em);

    for (int i = 0; i < em->size; i++) {
        const Enemy* enemy = &em->enemies[i];

        DrawRectangleRec(enemy->rect, enemy->color);
    }
}

int main(void) {
    srand((unsigned int) time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless Runner");

    int  score     = 0;
    bool game_over = false;

    Player player;
    player_init(&player);

    EnemyManager em;
    em_init(&em);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        if (!game_over) {
            player_update(&player, dt);
            em_update(&em, dt);

            // player collision enemy
            for (int i = 0; i < em.size; i++) {
                Enemy* enemy = &em.enemies[i];

                // update score
                if (!enemy->is_scored && player.rect.x > enemy->rect.x + enemy->rect.width) {
                    enemy->is_scored = true;
                    score++;
                }

                // game over
                if (CheckCollisionRecs(player.rect, enemy->rect)) {
                    game_over = true;
                    break;
                }
            }

        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                score     = 0;
                game_over = false;

                player_init(&player);
                em_init(&em);
            }
        }

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        // draw score
        DrawText(TextFormat("%d", score), 20, 10, 30, BLACK);

        player_draw(&player);
        em_draw(&em);

        if (game_over) {
            draw_centered_text(
                "GAME OVER", (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() - 50}, 30.0f);

            draw_centered_text("press ENTER to restart",
                               (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 50},
                               20.0f);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
