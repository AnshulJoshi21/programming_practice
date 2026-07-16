#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 600;

static const float GROUND_WIDTH = 40.0f;
static const int   GROUND_COLS  = SCREEN_WIDTH / (int) GROUND_WIDTH;

static const float JUMP_FORCE = 400.0f;
static const float GRAVITY    = 1200.0f;

static const float PLAYER_SIZE = 20.0f;

typedef enum CollisionType {
    COLLISION_NONE,

    COLLISION_LEFT,
    COLLISION_RIGHT,
    COLLISION_TOP,

} CollisionType;

static inline CollisionType aabb(Rectangle* player, const Rectangle* ground) {
    const float dx = (ground->x + ground->width / 2.0f) - (player->x + player->width / 2.0f);
    const float dy = (ground->y + ground->height / 2.0f) - (player->y + player->height / 2.0f);

    const float total_half_w = (player->width + ground->width) / 2.0f;
    const float total_half_h = (player->height + ground->height) / 2.0f;

    const float px = total_half_w - fabsf(dx);
    const float py = total_half_h - fabsf(dy);

    if (px > 0 && py > 0) {
        if (px < py) {
            if (dx > 0) {
                player->x -= px;
                return COLLISION_LEFT;
            } else {
                player->x += px;
                return COLLISION_RIGHT;
            }
        } else {
            if (dy > 0) {
                player->y -= py;
                return COLLISION_TOP;
            }
        }
    }
    return COLLISION_NONE;
}

typedef struct Player {
    Rectangle rect;
    Color     color;

    float hspeed;
    float vspeed;

    Vector2 direction;

    bool on_ground;
    bool on_left_wall;
    bool on_right_wall;
} Player;

static void player_init(Player* player) {
    assert(player);

    player->rect  = (Rectangle){0, 0, PLAYER_SIZE, PLAYER_SIZE};
    player->color = BLUE;

    player->hspeed = 250.0f;
    player->vspeed = 0.0f;

    player->direction = (Vector2){0, 0};

    player->on_ground     = false;
    player->on_left_wall  = false;
    player->on_right_wall = false;
}

static void player_draw(const Player* player) {
    assert(player);

    DrawRectangleRec(player->rect, player->color);
}

static void player_update(Player* player, const float dt) {
    assert(player);

    // horizontal movement
    player->direction.x = (float) IsKeyDown(KEY_D) - (float) IsKeyDown(KEY_A);
    player->direction   = Vector2Normalize(player->direction);

    player->rect.x += player->direction.x * player->hspeed * dt;

    // initiate jump;
    if (IsKeyPressed(KEY_SPACE)) {
        if (player->on_ground) {
            player->vspeed = -JUMP_FORCE;

        } else if (player->on_left_wall) {
            player->rect.x += 2.0f;
            player->vspeed = (-JUMP_FORCE * 75 / 100);

        } else if (player->on_right_wall) {
            player->rect.x -= 2.0f;
            player->vspeed = (-JUMP_FORCE * 75 / 100);
        }
    }

    // jumping
    player->vspeed += GRAVITY * dt;
    player->rect.y += player->vspeed * dt;

    // bounds
    player->rect.x = fmaxf(0.0f, fminf(player->rect.x, SCREEN_WIDTH - player->rect.width));
    player->rect.y = fmaxf(0.0f, fminf(player->rect.y, SCREEN_HEIGHT - player->rect.height));
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    Rectangle ground_arr[GROUND_COLS];

    for (int i = 0; i < GROUND_COLS; i++) {
        float rect_y      = GetRandomValue(100, SCREEN_HEIGHT - 10);
        float rect_height = SCREEN_HEIGHT - rect_y;

        ground_arr[i] = (Rectangle){i * GROUND_WIDTH, rect_y, GROUND_WIDTH, rect_height};
    }

    Player player;
    player_init(&player);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        player_update(&player, dt);

        player.on_ground     = false;
        player.on_left_wall  = false;
        player.on_right_wall = false;

        for (int i = 0; i < GROUND_COLS; i++) {
            CollisionType collision = aabb(&player.rect, &ground_arr[i]);

            if (collision == COLLISION_TOP)
                player.on_ground = true;

            if (collision == COLLISION_LEFT)
                player.on_left_wall = true;

            if (collision == COLLISION_RIGHT)
                player.on_right_wall = true;

            if (player.vspeed > 0 && collision != COLLISION_NONE) {
                player.vspeed = 0.0f;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < GROUND_COLS; i++) {
            DrawRectangleRec(ground_arr[i], GRAY);
            DrawRectangleLinesEx(ground_arr[i], 2.0f, BLACK);
        }

        player_draw(&player);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
