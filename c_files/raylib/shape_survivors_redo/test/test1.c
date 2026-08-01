#include <assert.h>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_PROJECTILES 100
#define MAX_ORBITALS 8

// BASE BULLET
typedef struct BaseBullet {
    Vector2 center;
    float   radius;
    Color   color;
    float   damage;
    float   lifetime;
} BaseBullet;

static void base_bullet_draw(const BaseBullet* bullet) {
    assert(bullet);

    DrawCircleV(bullet->center, bullet->radius, bullet->color);
}

static void base_bullet_update_lifetime(BaseBullet* bullet, const float dt) {
    assert(bullet);

    bullet->lifetime -= dt;
    if (bullet->lifetime <= 0.0f) {
        bullet->lifetime = 0.0f;
    }
}

// PROJECTILE
typedef struct ProjectileBullet {
    BaseBullet base;
    float      speed;
    Vector2    direction;
} ProjectileBullet;

static void projectile_bullet_init(ProjectileBullet* bullet,
                                   const Vector2     start_pos,
                                   const Vector2     target_pos) {
    assert(bullet);

    bullet->base.center   = start_pos;
    bullet->base.radius   = 5.0f;
    bullet->base.color    = RED;
    bullet->base.damage   = 1.0f;
    bullet->base.lifetime = 1.0f;
    bullet->speed         = 400.0f;

    // set direction
    const float dx       = target_pos.x - start_pos.x;
    const float dy       = target_pos.y - start_pos.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0)
        bullet->direction = (Vector2){dx / distance, dy / distance};
    else
        bullet->direction = (Vector2){0, 0};
}

static void projectile_bullet_update(ProjectileBullet* bullet, const float dt) {
    assert(bullet);

    // move
    bullet->base.center.x += bullet->direction.x * bullet->speed * dt;
    bullet->base.center.y += bullet->direction.y * bullet->speed * dt;

    base_bullet_update_lifetime(&bullet->base, dt);
}

// ORBITAL BULLET
typedef struct OrbitalBullet {
    BaseBullet     base;
    const Vector2* origin;
    float          angle;
    float          angular_radius;
    float          angular_speed;
} OrbitalBullet;

static void orbital_bullet_init(OrbitalBullet* bullet, const Vector2* origin, const float angle) {
    assert(bullet);
    assert(origin);

    const float angular_radius = 100.0f;

    bullet->base.center = (Vector2){
        origin->x + cosf(angle) * angular_radius,
        origin->y + sinf(angle) * angular_radius,
    };

    bullet->base.radius    = 10.0f;
    bullet->base.color     = BLACK;
    bullet->base.damage    = 5.0f;
    bullet->base.lifetime  = 10.0f;
    bullet->origin         = origin;
    bullet->angle          = angle;
    bullet->angular_radius = angular_radius;
    bullet->angular_speed  = 1.0f;
}

static void orbital_bullet_update(OrbitalBullet* bullet, const float dt) {
    assert(bullet);

    bullet->angle += bullet->angular_speed * dt;
    bullet->base.center = (Vector2){
        bullet->origin->x + cosf(bullet->angle) * bullet->angular_radius,
        bullet->origin->y + sinf(bullet->angle) * bullet->angular_radius,

    };

    base_bullet_update_lifetime(&bullet->base, dt);
}

// TIMER
typedef struct Timer {
    float elapsed;
    float duration;
} Timer;

static bool timer_tick(Timer* timer, const float dt) {
    assert(timer);

    timer->elapsed += dt;
    if (timer->elapsed >= timer->duration) {
        timer->elapsed -= timer->duration;
        return true;
    }
    return false;
}

// BULLET MANAGER
typedef struct BulletManager {
    ProjectileBullet projectiles[MAX_PROJECTILES];
    int              projectile_size;
    Timer            projectile_spawn_timer;

    OrbitalBullet orbitals[MAX_ORBITALS];
    int           orbital_size;
    Timer         orbital_spawn_timer;
} BulletManager;

static void spawn_projectile(BulletManager* bm,
                             const float    dt,
                             const Vector2  start_pos,
                             const Vector2  target_pos) {
    assert(bm);
    if (bm->projectile_size >= MAX_PROJECTILES)
        return;

    if (bm->projectile_size <= 0 || timer_tick(&bm->projectile_spawn_timer, dt)) {
        projectile_bullet_init(&bm->projectiles[bm->projectile_size++], start_pos, target_pos);
    }
}

static void spawn_orbitals(BulletManager* bm, const float dt, const Vector2* origin) {
    assert(bm);
    assert(origin);

    if (bm->orbital_size >= MAX_ORBITALS)
        return;

    if (bm->orbital_size <= 0 || timer_tick(&bm->orbital_spawn_timer, dt)) {
        const int temp   = bm->orbital_size + 1;
        bm->orbital_size = 0;

        for (int i = 0; i < temp; i++) {
            const float angle = (2 * PI * i) / temp;
            orbital_bullet_init(&bm->orbitals[i], origin, angle);
        }
        bm->orbital_size = temp;
    }
}

// PLAYER
typedef struct Player {
    Rectangle rect;
    Vector2   origin;
    float     rotation;
    Color     color;
    float     speed;
    Vector2   direction;
} Player;

static void player_init(Player* player) {
    assert(player);

    player->rect     = (Rectangle){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 40.0f, 40.0f};
    player->origin   = (Vector2){player->rect.width / 2.0f, player->rect.height / 2.0f};
    player->rotation = 0.0f;
    player->color    = BLUE;
    player->speed    = 300.0f;
    player->direction = (Vector2){0, 0};
}

static void player_update(Player* player, const float dt) {
    assert(player);

    // handle input
    player->direction.x = (float) IsKeyDown(KEY_D) - (float) IsKeyDown(KEY_A);
    player->direction.y = (float) IsKeyDown(KEY_S) - (float) IsKeyDown(KEY_W);
    player->direction   = Vector2Normalize(player->direction);

    // move
    player->rect.x += player->direction.x * player->speed * dt;
    player->rect.y += player->direction.y * player->speed * dt;

    // bounds
    player->rect.x = Clamp(player->rect.x, player->origin.x, GetScreenWidth() - player->origin.x);
    player->rect.y = Clamp(player->rect.y, player->origin.y, GetScreenHeight() - player->origin.y);
}

static void player_draw(const Player* player) {
    assert(player);

    DrawRectanglePro(player->rect, player->origin, player->rotation, player->color);
}

// MAIN
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bullet Test");

    BulletManager bullet_manager = (BulletManager){
        .projectile_size        = 0,
        .projectile_spawn_timer = {.elapsed = GetTime(), .duration = 0.5f},
        .orbital_size           = 0,
        .orbital_spawn_timer    = {.elapsed = GetTime(), .duration = 5.0f},
    };

    Player player;
    player_init(&player);

    while (!WindowShouldClose()) {
        // UPDATE
        const float dt = GetFrameTime();

        player_update(&player, dt);
        const Vector2 player_pos = (Vector2){player.rect.x, player.rect.y};

        spawn_projectile(&bullet_manager, dt, player_pos, GetMousePosition());
        spawn_orbitals(&bullet_manager, dt, &player_pos);

        // update projectiles
        for (int i = 0; i < bullet_manager.projectile_size; i++) {
            ProjectileBullet* projectile = &bullet_manager.projectiles[i];

            projectile_bullet_update(projectile, dt);

            // despawn
            if (projectile->base.lifetime <= 0) {
                bullet_manager.projectiles[i]
                    = bullet_manager.projectiles[--bullet_manager.projectile_size];
                i--;
            }
        }

        // update orbitals
        for (int i = 0; i < bullet_manager.orbital_size; i++) {
            OrbitalBullet* orbital = &bullet_manager.orbitals[i];
            orbital_bullet_update(orbital, dt);

            // despawn
            if (orbital->base.lifetime <= 0) {
                bullet_manager.orbitals[i] = bullet_manager.orbitals[--bullet_manager.orbital_size];
                i--;
            }

            // draw orbital lifetime:
            DrawText(TextFormat("O%d: %0.2f", i + 1, orbital->base.lifetime), 5, 30 * i, 20, BLACK);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // DRAW BULLETS
        for (int i = 0; i < bullet_manager.projectile_size; i++) {
            base_bullet_draw(&bullet_manager.projectiles[i].base);
        }
        for (int i = 0; i < bullet_manager.orbital_size; i++) {
            base_bullet_draw(&bullet_manager.orbitals[i].base);
        }

        player_draw(&player);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
