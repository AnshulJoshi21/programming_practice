// ============================================================
//  Minimal ECS in C + raylib
//  Techniques:
//    - Bitmask component flags (enum + uint32_t)
//    - Packed component arrays (parallel arrays per component)
//    - Count-and-swap-pop removal (O(1) entity removal)
//    - Systems iterate only matching entities
// ============================================================

#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ─── Constants ───────────────────────────────────────────────
#define MAX_ENTITIES    512
#define SCREEN_W        800
#define SCREEN_H        600
#define SPAWN_INTERVAL  0.5f   // seconds between enemy spawns

// ─── Component flags (bitmask) ───────────────────────────────
typedef enum {
    COMP_NONE       = 0,
    COMP_POSITION   = 1 << 0,   // 0x01
    COMP_VELOCITY   = 1 << 1,   // 0x02
    COMP_RENDER     = 1 << 2,   // 0x04
    COMP_HEALTH     = 1 << 3,   // 0x08
    COMP_ENEMY      = 1 << 4,   // 0x10
    COMP_BULLET     = 1 << 5,   // 0x20
    COMP_PLAYER     = 1 << 6,   // 0x40
    COMP_LIFETIME   = 1 << 7,   // 0x80
} ComponentMask;

// ─── Component data (parallel arrays) ────────────────────────
typedef struct { float x, y; }       CPosition;
typedef struct { float vx, vy; }     CVelocity;
typedef struct { Color color; float radius; } CRender;
typedef struct { int hp, maxHp; }    CHealth;
typedef struct { float remaining; }  CLifetime;

// ─── World ───────────────────────────────────────────────────
typedef struct {
    // Entity slots
    uint32_t    mask    [MAX_ENTITIES];   // component bitmask per entity

    // Component pools (parallel to entity index)
    CPosition   pos     [MAX_ENTITIES];
    CVelocity   vel     [MAX_ENTITIES];
    CRender     rend    [MAX_ENTITIES];
    CHealth     health  [MAX_ENTITIES];
    CLifetime   life    [MAX_ENTITIES];

    int count;   // number of live entities (packed [0..count-1])
} World;

// ─── Entity management ───────────────────────────────────────

// Returns index of new entity (tail of packed array)
int world_create(World *w) {
    if (w->count >= MAX_ENTITIES) return -1;
    int idx = w->count++;
    w->mask[idx] = COMP_NONE;
    return idx;
}

// Swap-pop removal: copy last entity over [idx], decrement count
void world_destroy(World *w, int idx) {
    int last = w->count - 1;
    if (idx != last) {
        w->mask  [idx] = w->mask  [last];
        w->pos   [idx] = w->pos   [last];
        w->vel   [idx] = w->vel   [last];
        w->rend  [idx] = w->rend  [last];
        w->health[idx] = w->health[last];
        w->life  [idx] = w->life  [last];
    }
    w->count--;
}

// ─── Helper macros ───────────────────────────────────────────
#define HAS(w, i, bits)  (((w)->mask[i] & (bits)) == (bits))
#define ADD(w, i, bits)  ((w)->mask[i] |= (bits))

// ─── Prefab factories ────────────────────────────────────────
int spawn_player(World *w, float x, float y) {
    int e = world_create(w);
    if (e < 0) return -1;
    ADD(w, e, COMP_POSITION | COMP_VELOCITY | COMP_RENDER | COMP_HEALTH | COMP_PLAYER);
    w->pos   [e] = (CPosition){ x, y };
    w->vel   [e] = (CVelocity){ 0, 0 };
    w->rend  [e] = (CRender){ SKYBLUE, 14.f };
    w->health[e] = (CHealth){ 5, 5 };
    return e;
}

int spawn_bullet(World *w, float x, float y, float vx, float vy) {
    int e = world_create(w);
    if (e < 0) return -1;
    ADD(w, e, COMP_POSITION | COMP_VELOCITY | COMP_RENDER | COMP_BULLET | COMP_LIFETIME);
    w->pos [e] = (CPosition){ x, y };
    w->vel [e] = (CVelocity){ vx, vy };
    w->rend[e] = (CRender){ YELLOW, 5.f };
    w->life[e] = (CLifetime){ 2.f };
    return e;
}

int spawn_enemy(World *w) {
    int e = world_create(w);
    if (e < 0) return -1;
    ADD(w, e, COMP_POSITION | COMP_VELOCITY | COMP_RENDER | COMP_HEALTH | COMP_ENEMY);
    float side = (float)(GetRandomValue(0, 3));
    float px, py, vx = 0, vy = 0;
    float spd = (float)GetRandomValue(60, 130);
    if (side < 1)      { px = GetRandomValue(0, SCREEN_W); py = -20;        vy =  spd; }
    else if (side < 2) { px = GetRandomValue(0, SCREEN_W); py = SCREEN_H+20; vy = -spd; }
    else if (side < 3) { px = -20;        py = GetRandomValue(0, SCREEN_H); vx =  spd; }
    else               { px = SCREEN_W+20; py = GetRandomValue(0, SCREEN_H); vx = -spd; }
    w->pos   [e] = (CPosition){ px, py };
    w->vel   [e] = (CVelocity){ vx, vy };
    w->rend  [e] = (CRender){ RED, 12.f };
    w->health[e] = (CHealth){ 3, 3 };
    return e;
}

// ─── Systems ─────────────────────────────────────────────────

// Movement system: POSITION + VELOCITY
void sys_movement(World *w, float dt) {
    uint32_t need = COMP_POSITION | COMP_VELOCITY;
    for (int i = 0; i < w->count; i++) {
        if (!HAS(w, i, need)) continue;
        w->pos[i].x += w->vel[i].vx * dt;
        w->pos[i].y += w->vel[i].vy * dt;
    }
}

// Lifetime / out-of-bounds removal system
// Uses count-and-swap-pop so we iterate carefully
void sys_cleanup(World *w, float dt) {
    for (int i = w->count - 1; i >= 0; i--) {
        // Tick lifetime
        if (HAS(w, i, COMP_LIFETIME)) {
            w->life[i].remaining -= dt;
            if (w->life[i].remaining <= 0.f) { world_destroy(w, i); continue; }
        }
        // Out of bounds (non-player)
        if (!HAS(w, i, COMP_PLAYER) && HAS(w, i, COMP_POSITION)) {
            float px = w->pos[i].x, py = w->pos[i].y;
            float margin = 80.f;
            if (px < -margin || px > SCREEN_W+margin ||
                py < -margin || py > SCREEN_H+margin) {
                world_destroy(w, i); continue;
            }
        }
    }
}

// Bullet vs Enemy collision
void sys_bullet_enemy(World *w, int *score) {
    for (int b = w->count - 1; b >= 0; b--) {
        if (!HAS(w, b, COMP_BULLET | COMP_POSITION | COMP_RENDER)) continue;
        float bx = w->pos[b].x, by = w->pos[b].y, br = w->rend[b].radius;

        for (int e = w->count - 1; e >= 0; e--) {
            if (!HAS(w, e, COMP_ENEMY | COMP_POSITION | COMP_HEALTH | COMP_RENDER)) continue;
            float ex = w->pos[e].x, ey = w->pos[e].y, er = w->rend[e].radius;
            float dx = bx - ex, dy = by - ey;
            if (dx*dx + dy*dy < (br+er)*(br+er)) {
                // Hit!
                w->health[e].hp--;
                world_destroy(w, b);  // bullet gone
                if (w->health[e].hp <= 0) { world_destroy(w, e); (*score)++; }
                break; // bullet destroyed, stop inner loop
            }
        }
    }
}

// Enemy vs Player collision
void sys_enemy_player(World *w, int playerIdx) {
    if (playerIdx < 0 || !HAS(w, playerIdx, COMP_POSITION | COMP_RENDER | COMP_HEALTH)) return;
    float px = w->pos[playerIdx].x, py = w->pos[playerIdx].y, pr = w->rend[playerIdx].radius;

    for (int e = w->count - 1; e >= 0; e--) {
        if (!HAS(w, e, COMP_ENEMY | COMP_POSITION | COMP_RENDER)) continue;
        float ex = w->pos[e].x, ey = w->pos[e].y, er = w->rend[e].radius;
        float dx = px - ex, dy = py - ey;
        if (dx*dx + dy*dy < (pr+er)*(pr+er)) {
            w->health[playerIdx].hp--;
            world_destroy(w, e);
        }
    }
}

// Render system: POSITION + RENDER
void sys_render(const World *w) {
    uint32_t need = COMP_POSITION | COMP_RENDER;
    for (int i = 0; i < w->count; i++) {
        if (!HAS(w, i, need)) continue;
        DrawCircle((int)w->pos[i].x, (int)w->pos[i].y,
                   w->rend[i].radius, w->rend[i].color);
        // Health bar for enemies and player
        if (HAS(w, i, COMP_HEALTH) && w->health[i].maxHp > 0) {
            float r = w->rend[i].radius;
            float barW = r * 2.f;
            float frac = (float)w->health[i].hp / (float)w->health[i].maxHp;
            DrawRectangle((int)(w->pos[i].x - r), (int)(w->pos[i].y - r - 8),
                          (int)barW, 4, DARKGRAY);
            DrawRectangle((int)(w->pos[i].x - r), (int)(w->pos[i].y - r - 8),
                          (int)(barW * frac), 4,
                          HAS(w, i, COMP_PLAYER) ? GREEN : ORANGE);
        }
    }
}

// Player input system — returns whether player is still alive
void sys_player_input(World *w, int playerIdx, float dt, float *shootCd) {
    if (playerIdx < 0 || !HAS(w, playerIdx, COMP_POSITION | COMP_VELOCITY)) return;
    const float SPD = 200.f, BSPD = 400.f;
    float vx = 0, vy = 0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    vy -= SPD;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  vy += SPD;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  vx -= SPD;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) vx += SPD;
    w->vel[playerIdx].vx = vx;
    w->vel[playerIdx].vy = vy;

    // Clamp to screen
    float r = w->rend[playerIdx].radius;
    if (w->pos[playerIdx].x < r) w->pos[playerIdx].x = r;
    if (w->pos[playerIdx].x > SCREEN_W-r) w->pos[playerIdx].x = SCREEN_W-r;
    if (w->pos[playerIdx].y < r) w->pos[playerIdx].y = r;
    if (w->pos[playerIdx].y > SCREEN_H-r) w->pos[playerIdx].y = SCREEN_H-r;

    // Shoot toward mouse
    *shootCd -= dt;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *shootCd <= 0.f) {
        *shootCd = 0.18f;
        float mx = (float)GetMouseX(), my = (float)GetMouseY();
        float dx = mx - w->pos[playerIdx].x, dy = my - w->pos[playerIdx].y;
        float len = sqrtf(dx*dx + dy*dy);
        if (len > 0.f) { dx /= len; dy /= len; }
        spawn_bullet(w, w->pos[playerIdx].x, w->pos[playerIdx].y, dx*BSPD, dy*BSPD);
    }
}

// ─── Find player index (searches packed array) ───────────────
int find_player(const World *w) {
    for (int i = 0; i < w->count; i++)
        if (HAS(w, i, COMP_PLAYER)) return i;
    return -1;
}

// ─── Main ────────────────────────────────────────────────────
int main(void) {
    SetRandomSeed(42);
    InitWindow(SCREEN_W, SCREEN_H, "Minimal ECS — C + raylib");
    SetTargetFPS(60);

    World *world = (World *)calloc(1, sizeof(World));

    spawn_player(world, SCREEN_W/2.f, SCREEN_H/2.f);

    float spawnTimer = 0.f;
    float shootCd    = 0.f;
    int   score      = 0;
    bool  gameOver   = false;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (!gameOver) {
            int playerIdx = find_player(world);
            if (playerIdx < 0 || world->health[playerIdx].hp <= 0) {
                gameOver = true;
            } else {
                // Input
                sys_player_input(world, playerIdx, dt, &shootCd);

                // Spawn enemies
                spawnTimer += dt;
                if (spawnTimer >= SPAWN_INTERVAL) {
                    spawnTimer = 0.f;
                    spawn_enemy(world);
                }

                // Update
                sys_movement(world, dt);
                sys_bullet_enemy(world, &score);
                sys_enemy_player(world, find_player(world));  // re-find after swaps
                sys_cleanup(world, dt);
            }
        } else {
            if (IsKeyPressed(KEY_R)) {
                // Restart
                memset(world, 0, sizeof(World));
                spawn_player(world, SCREEN_W/2.f, SCREEN_H/2.f);
                spawnTimer = 0.f; shootCd = 0.f; score = 0; gameOver = false;
            }
        }

        // ── Draw ──────────────────────────────────────────────
        BeginDrawing();
        ClearBackground((Color){15, 15, 25, 255});

        // Grid background
        for (int gx = 0; gx <= SCREEN_W; gx += 40)
            DrawLine(gx, 0, gx, SCREEN_H, (Color){30, 30, 50, 255});
        for (int gy = 0; gy <= SCREEN_H; gy += 40)
            DrawLine(0, gy, SCREEN_W, gy, (Color){30, 30, 50, 255});

        sys_render(world);

        // HUD
        DrawText(TextFormat("SCORE: %d", score), 12, 12, 20, WHITE);
        DrawText(TextFormat("ENTITIES: %d", world->count), 12, 36, 16, GRAY);
        int pidx = find_player(world);
        if (pidx >= 0 && HAS(world, pidx, COMP_HEALTH))
            DrawText(TextFormat("HP: %d", world->health[pidx].hp), 12, 56, 16, GREEN);
        DrawText("WASD move  LMB shoot", SCREEN_W - 200, 12, 14, DARKGRAY);

        if (gameOver) {
            DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0,0,0,160});
            DrawText("GAME OVER", SCREEN_W/2 - 100, SCREEN_H/2 - 40, 40, RED);
            DrawText(TextFormat("Score: %d", score), SCREEN_W/2 - 60, SCREEN_H/2 + 10, 24, WHITE);
            DrawText("Press R to restart", SCREEN_W/2 - 90, SCREEN_H/2 + 45, 20, GRAY);
        }

        EndDrawing();
    }

    free(world);
    CloseWindow();
    return 0;
}

/*
 * BUILD (Linux/macOS with raylib installed):
 *   gcc ecs_raylib.c -o ecs_raylib -lraylib -lm
 *
 * BUILD (Windows with raylib via vcpkg or manual):
 *   cl ecs_raylib.c /link raylib.lib opengl32.lib gdi32.lib winmm.lib
 *
 * Or with CMake / makefile — just link raylib + math.
 *
 * ─── ECS Architecture summary ─────────────────────────────
 *
 *  Entities  : integer indices [0, world.count)
 *  Components: parallel arrays (pos[], vel[], rend[], …)
 *  Bitmasks  : world.mask[i] flags which components entity i owns
 *  Systems   : iterate world.count, skip entities missing required bits
 *
 *  Removal (count-and-swap-pop):
 *    1. Copy last entity's data over the slot to remove.
 *    2. Decrement world.count.
 *    3. No holes, O(1), cache-friendly.
 *    ⚠ Entity indices change after removal — always re-find
 *      the player index when needed (find_player()).
 */
