#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MAX_PROJECTILE_BULLETS 1000
#define MAX_ORBITAL_BULLETS 10

typedef enum BulletPattern {
    BULLET_PATTERN_PROJECTILE,
    BULLET_PATTERN_ORBITAL,
    BULLET_PATTERN_MAX,

} BulletPattern;

// PROJECTILE
typedef enum ProjectileType {
    PROJECTILE_TYPE_MAGIC_MISSILES,
    PROJECTILE_TYPE_MAX,
} ProjectileType;

typedef struct ProjectileDef {
    BulletPattern pattern;
    const char*   name;
    float         radius;
    Color         color;
    float         speed;
    float         damage;
    float         lifetime;
} ProjectileDef;

static const ProjectileDef projectile_db[PROJECTILE_TYPE_MAX] = {
    [PROJECTILE_TYPE_MAGIC_MISSILES] = {.pattern  = BULLET_PATTERN_PROJECTILE,
                                        .name     = "Magic Missiles",
                                        .radius   = 5.0f,
                                        .color    = RED,
                                        .speed    = 300.0f,
                                        .damage   = 1.0f,
                                        .lifetime = 1.0f},
};

typedef struct ProjectileConfig {
    ProjectileType type;
    int            level;
    const Vector2  center;
    bool           homing;
    const Vector2* target;
} ProjectileConfig;

typedef struct ProjectileBullet {
    ProjectileType type;
    Vector2        center;
    float          speed;
    Vector2        direction;
    float          damage;
    float          lifetime;
    bool           homing;
    const Vector2* target;
} ProjectileBullet;

// TODO: SCALE BULLET VALUES BASED ON CONFIG->LEVEL
void projectile_init(ProjectileBullet* projectile, const ProjectileConfig* config) {
    assert(projectile);
    assert(config);

    projectile->type         = config->type;
    const ProjectileDef* def = &projectile_db[projectile->type];

    projectile->center = config->center;

    projectile->homing   = config->homing;
    projectile->speed    = def->speed;
    projectile->lifetime = def->lifetime;
    projectile->lifetime = def->lifetime;

    // set direction
    const float dx        = config->target->x - config->center.x;
    const float dy        = config->target->y - config->center.y;
    const float distance  = sqrtf((dx * dx) + (dy * dy));
    projectile->direction = (Vector2){0, 0};
    if (distance > 0) {
        projectile->direction = (Vector2){dx / distance, dy / distance};
    }

    if (config->homing) {
        assert(config->target);
        projectile->target = config->target;
    } else {
        projectile->target = NULL;
    }
}

void projectile_update(ProjectileBullet* projectile, const float dt) {
    assert(projectile);

    // update lifetime
    projectile->lifetime -= dt;
    if (projectile->lifetime <= 0) {
        projectile->lifetime = 0;
    }

    // set direction
    if (projectile->homing) {
        const float dx        = projectile->target->x - projectile->center.x;
        const float dy        = projectile->target->y - projectile->center.y;
        const float distance  = sqrtf((dx * dx) + (dy * dy));
        projectile->direction = (Vector2){0, 0};
        if (distance > 0) {
            projectile->direction = (Vector2){dx / distance, dy / distance};
        }
    }

    // move
    projectile->center.x += projectile->direction.x * projectile->speed * dt;
    projectile->center.y += projectile->direction.y * projectile->speed * dt;
}

void projectile_draw(const ProjectileBullet* projectile) {
    assert(projectile);
    const ProjectileDef* def = &projectile_db[projectile->type];

    DrawCircleV(projectile->center, def->radius, def->color);
}

// ORBITAL
typedef enum OrbitalType {
    ORBITAL_TYPE_ORBITING_ORBS,
    ORBITAL_TYPE_MAX,
} OrbitalType;

typedef struct OrbitalDef {
    BulletPattern pattern;
    const char*   name;
    int           max_count;
    float         radius;
    Color         color;
    float         orbital_radius;
    float         orbital_speed;
    float         damage;
    float         lifetime;
} OrbitalDef;

static const OrbitalDef orbital_db[ORBITAL_TYPE_MAX] = {
    [ORBITAL_TYPE_ORBITING_ORBS] = {.pattern        = BULLET_PATTERN_ORBITAL,
                                    .name           = "Orbiting Orbs",
                                    .max_count      = 10,
                                    .radius         = 10.0f,
                                    .color          = BLUE,
                                    .orbital_radius = 100.0f,
                                    .orbital_speed  = 1.0f,
                                    .damage         = 5.0f,
                                    .lifetime       = 5.0f},
};

typedef struct OrbitalConfig {
    OrbitalType    type;
    int            level;
    int            start_index;
    const Vector2  center;
    const Vector2* origin;
    float          angle; // angle = angle + (index * angle_step)
    bool           always_active;
} OrbitalConfig;

typedef struct OrbitalBullet {
    OrbitalType    type;
    int            level;
    int            start_index;
    Vector2        center;
    const Vector2* origin;
    float          angle;
    float          lifetime;
    bool           always_active;
} OrbitalBullet;

// TODO: SCALE BULLET VALUES BASED ON CONFIG->LEVEL
void orbital_init(OrbitalBullet* orbital, const OrbitalConfig* config) {
    assert(orbital);
    assert(config);

    orbital->type         = config->type;
    const OrbitalDef* def = &orbital_db[orbital->type];
    orbital->level        = config->level;

    orbital->center        = config->center;
    orbital->origin        = config->origin;
    orbital->always_active = config->always_active;
    if (orbital->always_active)
        orbital->lifetime = 0;
    else
        orbital->lifetime = def->lifetime;
}

void orbital_update(OrbitalBullet* orbital, const float dt) {
    assert(orbital);
    const OrbitalDef* def = &orbital_db[orbital->type];

    orbital->angle += def->orbital_speed * dt;
    orbital->center = (Vector2){
        orbital->origin->x + cosf(orbital->angle) * def->orbital_radius,
        orbital->origin->y + cosf(orbital->angle) * def->orbital_radius,
    };

    // update lifetime
    if (!orbital->always_active) {
        orbital->lifetime -= dt;
        if (orbital->lifetime <= 0)
            orbital->lifetime = 0;
    }
}

void orbital_draw(const OrbitalBullet* orbital) {
    assert(orbital);
    const OrbitalDef* def = &orbital_db[orbital->type];

    DrawCircleV(orbital->center, def->radius, def->color);
}

// BULLET MANAGER
typedef struct BulletManager {
    ProjectileBullet projectiles[MAX_PROJECTILE_BULLETS];
    int              projectile_count;
    OrbitalBullet    orbitals[MAX_ORBITAL_BULLETS];
    int              orbital_count;
    int              orbiting_orbs_count;
} BulletManager;

void bullet_manager_init(BulletManager* bm) {
    assert(bm);

    bm->projectile_count = 0;
    bm->orbital_count    = 0;
}

void bullet_manager_spawn(BulletManager*          bm,
                          const ProjectileConfig* pconfig,
                          const OrbitalConfig*    oconfig) {
    assert(bm);

    if (pconfig) {
        if (bm->projectile_count >= MAX_PROJECTILE_BULLETS)
            return;

        projectile_init(&bm->projectiles[bm->projectile_count], pconfig);
        bm->projectile_count++;
    }

    if (oconfig) {
        if (bm->orbital_count >= MAX_ORBITAL_BULLETS)
            return;

        orbital_init(&bm->orbitals[bm->orbital_count], oconfig);
        bm->orbital_count++;
    }
}

void bullet_manager_despawn(BulletManager* bm, const BulletPattern pattern, const int index) {
    assert(bm);

    switch (pattern) {
        case BULLET_PATTERN_PROJECTILE: {
            assert(index >= 0 && index < bm->projectile_count);

            bm->projectiles[index] = bm->projectiles[bm->projectile_count - 1];
            bm->projectile_count--;
        } break;
        case BULLET_PATTERN_ORBITAL: {
            assert(index >= 0 && index < bm->orbiting_orbs_count);

            bm->orbitals[index] = bm->orbitals[bm->orbital_count - 1];
            bm->orbital_count--;
        } break;
        default:
            return;
    }
}

void bullet_manager_update(BulletManager* bm, const float dt) {
    assert(bm);

    // projectile updates
    for (int i = 0; i < bm->projectile_count; i++) {
        ProjectileBullet*    projectile = &bm->projectiles[i];
        const ProjectileDef* def        = &projectile_db[projectile->type];

        projectile_update(projectile, dt);

        if (projectile->lifetime <= 0) {
            bullet_manager_despawn(bm, def->pattern, i);
            i--;
        }
    }

    // orbital updates
    for (int i = 0; i < bm->orbital_count; i++) {
        OrbitalBullet*    orbital = &bm->orbitals[i];
        const OrbitalDef* def     = &orbital_db[orbital->type];

        orbital_update(orbital, dt);

        if (orbital->always_active)
            continue;

        if (orbital->lifetime <= 0) {
            bullet_manager_despawn(bm, def->pattern, i);
            i--;
        }
    }
}

void bullet_manager_draw(const BulletManager* bm) {
    assert(bm);

    // projectiles
    for (int i = 0; i < bm->projectile_count; i++) {
        projectile_draw(&bm->projectiles[i]);
    }

    // orbitals
    for (int i = 0; i < bm->orbital_count; i++) {
        orbital_draw(&bm->orbitals[i]);
    }
}

// MAIN
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Architecture Test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
