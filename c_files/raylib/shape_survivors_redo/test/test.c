#include <assert.h>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MAX_PROJECTILES 100
#define PROJECTILE_SPAWN_DURATION 0.5

#define MAX_ORBITALS 10
#define MAX_ORBITALS_LIFETIME 20.0f

#define PLAYER_SIZE 40.0f

// TIMER
typedef struct Timer {
    double elapsed;
    double duration;
} Timer;

static void timer_init(Timer* timer, const float duration) {
    assert(timer);

    timer->elapsed  = GetTime();
    timer->duration = duration;
}

static bool timer_tick(Timer* timer) {
    assert(timer);

    const float current_time = GetTime();
    if (current_time - timer->elapsed >= timer->duration) {
        timer->elapsed += timer->duration;
        return true;
    }
    return false;
}

// BACKGROUND GRID
static void draw_background_grid(void) {
    const float thick      = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = 100.0f;

    for (float x = 0; x < SCREEN_WIDTH; x += block_size) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, SCREEN_HEIGHT}, thick, color);
    }
    for (float y = 0; y < SCREEN_HEIGHT; y += block_size) {
        DrawLineEx((Vector2){0, y}, (Vector2){SCREEN_WIDTH, y}, thick, color);
    }
}

// GENERAL
typedef enum BulletPattern {
    BULLET_PATTERN_PROJECTILE,
    BULLET_PATTERN_ORBITAL,
    BULLET_PATTERN_AREA,
    BULLET_PATTERN_MAX,
} BulletPattern;

typedef enum DamageMode {
    DAMAGE_MODE_INSTANT_HIT,
    DAMAGE_MODE_TICK,
    DAMAGE_MODE_ON_EXPIRE,
    DAMAGE_MODE_MAX,
} DamageMode;

typedef struct EntityConfig {
    int type;
    int level;
} EntityConfig;

// PROJECTILEs
// DATA
typedef enum ProjectileType {
    PROJECTILE_TYPE_MAGIC_MISSILE,
    PROJECTILE_TYPE_MAX,
} ProjectileType;

typedef struct ProjectileDef {
    BulletPattern pattern;
    DamageMode    damage_mode;
    float         radius;
    Color         color;
    float         speed;
    float         damage;
    float         lifetime;
} ProjectileDef;

static const ProjectileDef projectile_db[PROJECTILE_TYPE_MAX]
    = {[PROJECTILE_TYPE_MAGIC_MISSILE] = {.pattern     = BULLET_PATTERN_PROJECTILE,
                                          .damage_mode = DAMAGE_MODE_INSTANT_HIT,
                                          .radius      = 5.0f,
                                          .color       = RED,
                                          .speed       = 400.0f,
                                          .damage      = 1.0f,
                                          .lifetime    = 1.0f}};

// IMPLEMENTATION
typedef struct Projectile {
    ProjectileType type;
    int            level;
    Vector2        center;
    Vector2        direction;
    float          lifetime;
} Projectile;

typedef struct ProjectileConfig {
    Vector2 start_pos;
    Vector2 target_pos;
} ProjectilConfig;

static void projectile_init(Projectile*            projectile,
                            const EntityConfig*    econfig,
                            const ProjectilConfig* pconfig) {
    assert(projectile);
    assert(econfig);
    assert(pconfig);

    const ProjectileDef* def = &projectile_db[econfig->type];

    projectile->type  = econfig->type;
    projectile->level = econfig->level;

    projectile->center   = pconfig->start_pos;
    projectile->lifetime = def->lifetime;

    const float dx       = pconfig->target_pos.x - pconfig->start_pos.x;
    const float dy       = pconfig->target_pos.y - pconfig->start_pos.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0)
        projectile->direction = (Vector2){};
}

static void projectile_update(Projectile* projectile, const float dt) {
    assert(projectile);
    const ProjectileDef* def = &projectile_db[projectile->type];

    // move
    projectile->center.x += projectile->direction.x * def->speed * dt;
    projectile->center.y += projectile->direction.y * def->speed * dt;

    // update lifetime
    projectile->lifetime -= dt;
    if (projectile->lifetime <= 0) {
        projectile->lifetime = 0.0f;
    }
}

// ORBITALs
// DATA
typedef enum OrbitalType {
    ORBITAL_TYPE_ORBITING_ORBS,
    ORBITAL_TYPE_MAX,
} OrbitalType;

typedef struct OrbitalDef {
    BulletPattern pattern;
    DamageMode    damage_mode;
    float         radius;
    Color         color;
    float         angular_radius;
    float         angular_speed;
    float         damage;
} OrbitalDef;

static const OrbitalDef orbital_db[ORBITAL_TYPE_MAX] = {[ORBITAL_TYPE_ORBITING_ORBS] = {
                                                            .pattern     = BULLET_PATTERN_ORBITAL,
                                                            .damage_mode = DAMAGE_MODE_INSTANT_HIT,
                                                            .radius      = 10.0f,
                                                            .color       = BLACK,
                                                            .angular_radius = 100.0f,
                                                            .angular_speed  = 1.0f,
                                                            .damage         = 5.0f,
                                                        }};

// IMPLEMENTATION
typedef struct Orbital {
    OrbitalType    type;
    int            level;
    Vector2        center;
    const Vector2* origin;
    float          angle;
} Orbital;

typedef struct OrbitalConfig {
    const Vector2* origin;
    float          angle;
} OrbitalConfig;

static void
orbital_init(Orbital* orbital, const EntityConfig* econfig, const OrbitalConfig* pconfig) {
    assert(orbital);
    assert(econfig);
    assert(pconfig);

    const OrbitalDef* def = &orbital_db[econfig->type];

    orbital->type  = econfig->type;
    orbital->level = econfig->level;

    orbital->center = (Vector2){
        pconfig->origin->x + cosf(pconfig->angle) * def->angular_radius,
        pconfig->origin->y + sinf(pconfig->angle) * def->angular_radius,
    };
    orbital->origin = pconfig->origin;
    orbital->angle  = pconfig->angle;
}

static void orbital_update(Orbital* orbital, const float dt) {
    assert(orbital);
    const OrbitalDef* def = &orbital_db[orbital->type];

    orbital->angle += def->angular_speed * dt;

    orbital->center = (Vector2){
        orbital->origin->x + cosf(orbital->angle) * def->angular_radius,
        orbital->origin->y + sinf(orbital->angle) * def->angular_radius,
    };
}

// BULLET MANAGER
typedef struct BulletManager {
    Projectile projectiles[MAX_PROJECTILES];
    int        projectile_count;
    Timer      projectile_timer;

    Orbital orbitals[MAX_ORBITALS];
    int     orbital_count;
    int     orbitals_lifetime;
} BulletManager;

static void bullet_manager_spawn_projectile(BulletManager*         bm,
                                            const EntityConfig*    econfig,
                                            const ProjectilConfig* pconfig) {
    assert(bm);
    assert(econfig);
    assert(pconfig);

    if (bm->projectile_count >= MAX_PROJECTILES)
        return;

    if (bm->projectile_count <= 0 || timer_tick(&bm->projectile_timer)) {
        projectile_init(&bm->projectiles[bm->projectile_count++], econfig, pconfig);
    }
}

static void bullet_manager_update(BulletManager* bm, const float dt) {
    assert(bm);

    // projectiles
    for (int i = 0; i < bm->projectile_count; i++) {
        Projectile* projectile = &bm->projectiles[i];

        projectile_update(projectile, dt);

        if (projectile->lifetime <= 0) {
            bm->projectiles[i] = bm->projectiles[--bm->projectile_count];
            i--;
        }
    }

    // orbitals
    for (int i = 0; i < bm->orbital_count; i++) {
        Orbital* orbital = &bm->orbitals[i];

        orbital_update(orbital, dt);
    }

    bm->orbitals_lifetime -= dt;
    if (bm->orbitals_lifetime <= 0.0f) {
        bm->orbitals_lifetime = 0.0f;
        bm->orbital_count     = 0;
    }
}

static void bullet_manager_draw(const BulletManager* bm) {
    assert(bm);

    // projectile
    for (int i = 0; i < bm->projectile_count; i++) {
        const Projectile*    projectile = &bm->projectiles[i];
        const ProjectileDef* def        = &projectile_db[projectile->type];
        DrawCircleV(projectile->center, def->radius, def->color);
    }

    // orbital
    for (int i = 0; i < bm->orbital_count; i++) {
        const Orbital*    orbital = &bm->orbitals[i];
        const OrbitalDef* def     = &orbital_db[orbital->type];
        DrawCircleV(orbital->center, def->radius, def->color);
    }
}

// PLAYER
typedef struct Player {
    Rectangle rect;
    Color     color;
    float     speed;
    Vector2   direction;
} Player;

static void player_init(Player* player) {
    assert(player);

    player->rect = (Rectangle){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, PLAYER_SIZE, PLAYER_SIZE};
    player->color     = BLUE;
    player->speed     = 300.0f;
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

    // set bounds
    player->rect.x = Clamp(player->rect.x, PLAYER_SIZE / 2.0f, SCREEN_WIDTH - PLAYER_SIZE / 2.0f);
    player->rect.y = Clamp(player->rect.y, PLAYER_SIZE / 2.0f, SCREEN_HEIGHT - PLAYER_SIZE / 2.0f);
}

static void player_draw(const Player* player) {
    assert(player);

    const Vector2 origin = (Vector2){PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f};
    DrawRectanglePro(player->rect, origin, 0.0f, player->color);
}

// MAIN
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Code Organization Test");

    Player player;
    player_init(&player);

    BulletManager bullet_manager = (BulletManager){
        .projectile_count  = 0,
        .orbital_count     = 0,
        .orbitals_lifetime = MAX_ORBITALS_LIFETIME,
    };
    timer_init(&bullet_manager.projectile_timer, PROJECTILE_SPAWN_DURATION);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        player_update(&player, dt);
        bullet_manager_update(&bullet_manager, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_background_grid();

        player_draw(&player);
        bullet_manager_draw(&bullet_manager);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
