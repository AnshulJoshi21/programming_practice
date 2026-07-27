#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MAX_PROJECTILES 500
#define MAX_ORBITALS 8

typedef enum BulletPattern {
    PATTERN_PROJECTILE,
    PATTERN_ORBITAL,
    PATTERN_AREA,
    PATTERN_MAX,
} BulletPattern;

typedef enum DamageMode {
    DAMAGE_INSTANT,
    DAMAGE_TICK,
    DAMAGE_ON_EXPIRE,
    DAMAGE_MODE_MAX,
} DamageMode;

// PROJECTILE
typedef enum ProjectileType {
    PROJECTILE_MAGIC_MISSILE,
    PROJECTILE_MAX,
} ProjectileType;

typedef struct ProjectileDef {
    const char*   name;
    BulletPattern pattern;
    float         radius;
    Color         color;
    float         speed;
    float         damage;
    float         lifetime;
} ProjectileDef;

static const ProjectileDef projectile_db[PROJECTILE_MAX] = {
    [PROJECTILE_MAGIC_MISSILE] = {.name     = "Magic Missile",
                                  .pattern  = PATTERN_PROJECTILE,
                                  .radius   = 5.0f,
                                  .color    = RED,
                                  .speed    = 300.0f,
                                  .damage   = 1.0f,
                                  .lifetime = 1.0f},
};

typedef struct ProjectileConfig {
    ProjectileType type;
    int            level;
    bool           homing;
    Vector2        start_pos;
    Vector2*       target_pos;
} ProjectileConfig;

typedef struct Projectile {
    ProjectileType type;
    int            level;
    Vector2        center;
    Vector2        direction;
    float          lifetime;
    bool           homing;
    const Vector2* target_pos;
} Projectile;

static void projectile_init(Projectile* p, const ProjectileConfig* config) {
    assert(p);
    assert(config);
    const ProjectileDef* def = &projectile_db[config->type];

    p->type      = config->type;
    p->level     = config->level;
    p->center    = config->start_pos;
    p->lifetime  = def->lifetime;
    p->direction = (Vector2){0, 0};

    if (config->homing) {
        p->homing     = true;
        p->target_pos = config->target_pos;
    } else {
        p->homing     = false;
        p->target_pos = NULL;

        const float dx       = p->target_pos->x - p->center.x;
        const float dy       = p->target_pos->y - p->center.y;
        const float distance = sqrtf((dx * dx) + (dy * dy));
        if (distance > 0) {
            p->direction = (Vector2){dx / distance, dy / distance};
        }
    }
};

static void projectile_update(Projectile* p, const float dt) {
    assert(p);
    const ProjectileDef* def = &projectile_db[p->type];

    if (p->homing) {
        const float dx       = p->target_pos->x - p->center.x;
        const float dy       = p->target_pos->y - p->center.y;
        const float distance = sqrtf((dx * dx) + (dy * dy));
        if (distance > 0) {
            p->direction = (Vector2){dx / distance, dy / distance};
        }
    }

    // move
    p->center.x += p->direction.x * def->speed * dt;
    p->center.y += p->direction.y * def->speed * dt;

    // update lifetime
    p->lifetime -= dt;
    if (p->lifetime <= 0) {
        p->lifetime = 0;
    }
}

// ORBITALS
typedef enum OrbitalType {
    ORBITAL_TYPE_ORBITING_ORBS,
    ORBITAL_TYPE_MAX,
} OrbitalType;

typedef struct OrbitalDef {
    const char*   name;
    BulletPattern pattern;
    float         radius;
    Color         color;
    float         orbital_radius;
    float         orbital_speed;
    float         lifetime;
} OrbitalDef;

static const OrbitalDef orbital_db[ORBITAL_TYPE_MAX] = {
    [ORBITAL_TYPE_ORBITING_ORBS] ={
        .name = "Orbiting Orbs",
        .pattern = PATTERN_ORBITAL,
        .radius = 10.0f,
        .color = BLACK,
        .orbital_radius = 100.0f,
        .orbital_speed = 1.0f,
        .lifetime = 5.0f,
    },
};

typedef struct OrbitalConfig {
    OrbitalType    type;
    int            level;
    Vector2        start_pos;
    const Vector2* origin;
} OrbitalConfig;

typedef struct Orbital {
    OrbitalType    type;
    int            level;
    Vector2        center;
    const Vector2* origin;
    float          angle;
    float          lifetime;
} Orbital;

static void orbital_init(Orbital* o, const OrbitalConfig* config) {
    assert(o);
    assert(config);
    const OrbitalDef* def = &orbital_db[config->type];

    o->type     = config->type;
    o->level    = config->level;
    o->center   = config->start_pos;
    o->origin   = config->origin;
    o->angle    = 0.0f;
    o->lifetime = def->lifetime;
}

static void orbital_update(Orbital* o, const float dt, const float angle_offset) {
    assert(o);
    const OrbitalDef* def = &orbital_db[o->type];

    o->angle += def->orbital_speed * dt;
    o->center = (Vector2){
        o->origin->x + cosf(o->angle + angle_offset) * def->orbital_radius,
        o->origin->y + sinf(o->angle + angle_offset) * def->orbital_radius,
    };

    // update lifetime
    o->lifetime -= dt;
    if (o->lifetime <= 0)
        o->lifetime = 0;
}

// AREA

// BULLET Manager
typedef struct BulletManager {
    Projectile projectiles[MAX_PROJECTILES];
    int        p_size;
    Orbital    orbitals[MAX_ORBITALS];
    int        o_size;
} BulletManager;

static void bullet_manager_init(BulletManager* bm) {
    assert(bm);
    bm->p_size = 0;
    bm->o_size = 0;
}

static void bullet_manager_spawn_projectile(BulletManager* bm, const ProjectileConfig* config) {
    assert(bm);
    if (bm->p_size >= MAX_PROJECTILES)
        return;

    projectile_init(&bm->projectiles[bm->p_size], config);
    bm->p_size++;
}

static void bullet_manager_spawn_orbital(BulletManager* bm, const OrbitalConfig* config) {
    assert(bm);
    if (bm->o_size >= MAX_ORBITALS)
        return;

    orbital_init(&bm->orbitals[bm->o_size], config);
    bm->o_size++;
}

static void
bullet_manager_despawn(BulletManager* bm, const BulletPattern pattern, const int index) {
    assert(bm);

    switch (pattern) {
        case PATTERN_PROJECTILE: {
            assert(index >= 0 && index < bm->p_size);
            bm->projectiles[index] = bm->projectiles[bm->p_size - 1];
            bm->p_size--;
        } break;

        case PATTERN_ORBITAL: {
            assert(index >= 0 && index < bm->o_size);
            bm->orbitals[index] = bm->orbitals[bm->o_size - 1];
            bm->o_size--;
        } break;

        case PATTERN_AREA: {
        } break;

        default:
            return;
    }
}

static void bullet_manager_update(BulletManager* bm, const float dt) {
    assert(bm);

    // projectile
    for (int i = 0; i < bm->p_size; i++) {
        Projectile*          p   = &bm->projectiles[i];
        const ProjectileDef* def = &projectile_db[p->type];

        projectile_update(p, dt);

        if (p->lifetime <= 0) {
            bullet_manager_despawn(bm, def->pattern, i);
            i--;
        }
    }

    // orbital
    for (int i = 0; i < bm->o_size; i++) {
        Orbital*          o   = &bm->orbitals[i];
        const OrbitalDef* def = &orbital_db[o->type];

        const float angle_offset = (2 * PI * i) / bm->o_size;
        orbital_update(o, dt, angle_offset);

        if (o->lifetime <= 0) {
            bullet_manager_despawn(bm, def->pattern, i);
            i--;
        }
    }
}

static void bullet_manager_draw(const BulletManager* bm) {
    assert(bm);

    // PROJECTILES
    for (int i = 0; i < bm->p_size; i++) {
        const Projectile*    p   = &bm->projectiles[i];
        const ProjectileDef* def = &projectile_db[p->type];
        DrawCircleV(p->center, def->radius, def->color);
    }

    // ORBITALS
    for (int i = 0; i < bm->o_size; i++) {
        const Orbital*    o   = &bm->orbitals[i];
        const OrbitalDef* def = &orbital_db[o->type];
        DrawCircleV(o->center, def->radius, def->color);
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bullet Test");

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
