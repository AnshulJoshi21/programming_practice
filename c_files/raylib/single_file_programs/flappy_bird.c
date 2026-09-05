#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

static const int   SCREEN_WIDTH  = 800;
static const int   SCREEN_HEIGHT = 600;
static const float JUMP_FORCE    = 550;
static const float GRAVITY       = 1200;

static const float PILLAR_HORIZONTAL_GAP = SCREEN_WIDTH / 2.0f;
static const float PILLAR_VERTICAL_GAP   = 200.0f;

#define MAX_PILLARS 10

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
} Player;

static void player_init(Player* player) {
    assert(player);

    const float width  = 40.0f;
    const float height = 40.0f;
    const float x      = GetScreenWidth() / 2.0f;
    const float y      = GetScreenHeight() / 2.0f;

    player->rect     = (Rectangle){x, y, width, height};
    player->color    = DARKBLUE;
    player->change_y = 0.0f;
}

static void player_update(Player* player, const float dt) {
    assert(player);

    // initiate jump
    if (IsKeyPressed(KEY_W)) {
        player->change_y = -JUMP_FORCE;
    }

    player->change_y += GRAVITY * dt;
    player->rect.y += player->change_y * dt;

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
} Pillar;

static void pillar_init(Pillar* pillar) {
    assert(pillar);

    const float width  = 100.0f;
    const float height = randf(0, GetScreenHeight() - PILLAR_VERTICAL_GAP);
    pillar->rect       = (Rectangle){GetScreenWidth(), 0, width, height};
    pillar->color      = DARKGREEN;
    pillar->is_scored  = false;
}

typedef struct {
    Pillar pillars[MAX_PILLARS];
    int    size;
    float  speed;
    float  speed_increment;
} PillarManager;

static void pm_init(PillarManager* pm) {
    assert(pm);

    pm->size            = 0;
    pm->speed           = 100.0f;
    pm->speed_increment = 10.0f;
}

static void pm_update(PillarManager* pm, const float dt) {
    assert(pm);

    pm->speed += pm->speed_increment * dt;

    // spawn
    if (pm->size < MAX_PILLARS) {
        const Pillar* last_pillar = &pm->pillars[pm->size - 1];
        if (pm->size == 0
            || last_pillar->rect.x + last_pillar->rect.width + PILLAR_HORIZONTAL_GAP
                   < GetScreenWidth()) {
            //
            pillar_init(&pm->pillars[pm->size]);
            pm->size++;
        }
    }

    // update
    for (int i = 0; i < pm->size; i++) {
        Pillar* pillar = &pm->pillars[i];

        // move
        pillar->rect.x -= pm->speed * dt;

        // despawn
        if (pillar->rect.x + (pillar->rect.width * 2) < 0) {
            pm->pillars[i] = pm->pillars[--pm->size];
            i--;
        }
    }
}

static void pm_draw(const PillarManager* pm) {
    assert(pm);

    for (int i = 0; i < pm->size; i++) {
        const Pillar* pillar = &pm->pillars[i];

        // top pillar
        DrawRectangleRec(pillar->rect, pillar->color);

        // bottom pillar
        const float bottom_y      = pillar->rect.y + pillar->rect.height + PILLAR_VERTICAL_GAP;
        const float bottom_height = GetScreenHeight() - bottom_y;
        DrawRectangleRec((Rectangle){pillar->rect.x, bottom_y, pillar->rect.width, bottom_height},
                         pillar->color);
    }
}

int main(void) {
    srand((unsigned int) time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");

    int  score       = 0;
    bool game_active = false;
    bool game_over   = false;

    Player player;
    player_init(&player);

    PillarManager pm;
    pm_init(&pm);

    while (!WindowShouldClose()) {
        // activate game
        if (IsKeyPressed(KEY_SPACE)) {
            game_active = true;
        }

        if (game_active && !game_over) {
            const float dt = GetFrameTime();

            player_update(&player, dt);
            pm_update(&pm, dt);

            // hit ground
            if (player.rect.y + player.rect.height == GetScreenHeight()) {
                game_over = true;
                continue;
            }

            for (int i = 0; i < pm.size; i++) {
                Pillar* pillar = &pm.pillars[i];

                // update score
                if (!pillar->is_scored && player.rect.x > pillar->rect.x + pillar->rect.width) {
                    pillar->is_scored = true;
                    score++;
                }

                // game over
                // top pillar
                if (CheckCollisionRecs(player.rect, pillar->rect)) {
                    game_over = true;
                    break;
                }

                // bottom pillar
                const float bottom_y = pillar->rect.y + pillar->rect.height + PILLAR_VERTICAL_GAP;
                const float bottom_height = GetScreenHeight() - bottom_y;
                if (CheckCollisionRecs(
                        player.rect,
                        (Rectangle){pillar->rect.x, bottom_y, pillar->rect.width, bottom_height})) {
                    game_over = true;
                    break;
                }
            }

        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                score       = 0;
                game_active = false;
                game_over   = false;

                player_init(&player);
                pm_init(&pm);
            }
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);

        if (!game_active && !game_over) {
            draw_centered_text("press SPACE to begin",
                               (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200},
                               20.0f);
        }

        player_draw(&player);
        pm_draw(&pm);

        if (game_over) {
            const char* text = "GAME OVER";

            const float     width     = 300.0f;
            const float     height    = 150.0f;
            const Rectangle rect      = (Rectangle){(GetScreenWidth() - width) / 2.0f,
                                                    (GetScreenHeight() - height) / 2.0f,
                                                    width,
                                                    height};
            const Color     color     = BLACK;
            const float     thickness = 5.0f;

            draw_centered_text(text, rect, 30.0f);
            draw_centered_text("press ENTER to restart",
                               (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200},
                               20.0f);

            // draw outline rect
            DrawRectangleLinesEx(rect, thickness, color);
        }

        // draw score
        DrawText(TextFormat("%d", score), 20, 20, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
