#include <assert.h>
#include <raylib.h>

static const int SCREEN_WIDTH  = 1280;
static const int SCREEN_HEIGHT = 720;

static const int   SPRITE_SIZE  = 256;
static const float PLAYER_SCALE = 1.0f;

typedef enum {
    ANIMATION_TYPE_BOW_SHOT,
    ANIMATION_TYPE_DEATH_BARE,
    ANIMATION_TYPE_DEATH_BOW,
    ANIMATION_TYPE_DEATH_STAFF,
    ANIMATION_TYPE_DEATH_SWORD,
    ANIMATION_TYPE_HURT_BARE,
    ANIMATION_TYPE_HURT_BOW,
    ANIMATION_TYPE_HURT_STAFF,
    ANIMATION_TYPE_HURT_SWORD,
    ANIMATION_TYPE_IDLE_BARE,
    ANIMATION_TYPE_IDLE_BOW,
    ANIMATION_TYPE_IDLE_STAFF,
    ANIMATION_TYPE_IDLE_SWORD,
    ANIMATION_TYPE_JUMP_BARE,
    ANIMATION_TYPE_JUMP_BOW,
    ANIMATION_TYPE_JUMP_STAFF,
    ANIMATION_TYPE_JUMP_SWORD,
    ANIMATION_TYPE_RUN_BARE,
    ANIMATION_TYPE_RUN_BOW,
    ANIMATION_TYPE_RUN_STAFF,
    ANIMATION_TYPE_RUN_SWORD,
    ANIMATION_TYPE_SHIELD_WALK,
    ANIMATION_TYPE_SHIELD_WALK_WITH_SWORD,
    ANIMATION_TYPE_STAB,
    ANIMATION_TYPE_STAFF_CAST,
    ANIMATION_TYPE_SWIPE,
    ANIMATION_TYPE_SWIPE2,
    ANIMATION_TYPE_WALK_BARE,
    ANIMATION_TYPE_WALK_BOW,
    ANIMATION_TYPE_WALK_STAFF,
    ANIMATION_TYPE_WALK_SWORD,

    ANIMATION_TYPE_MAX,
} AnimationType;

typedef struct {
    int   count;
    float duration;
    bool  loops;
} AnimationConfig;

static const AnimationConfig animation_config[ANIMATION_TYPE_MAX] = {
    [ANIMATION_TYPE_BOW_SHOT] = {.count = 13, .duration = 0.10f, .loops = false},

    [ANIMATION_TYPE_DEATH_BARE]  = {.count = 10, .duration = 0.10f, .loops = false},
    [ANIMATION_TYPE_DEATH_BOW]   = {.count = 10, .duration = 0.10f, .loops = false},
    [ANIMATION_TYPE_DEATH_STAFF] = {.count = 10, .duration = 0.10f, .loops = false},
    [ANIMATION_TYPE_DEATH_SWORD] = {.count = 10, .duration = 0.10f, .loops = false},

    [ANIMATION_TYPE_HURT_BARE]  = {.count = 3, .duration = 0.10f, .loops = false},
    [ANIMATION_TYPE_HURT_BOW]   = {.count = 3, .duration = 0.10f, .loops = false},
    [ANIMATION_TYPE_HURT_STAFF] = {.count = 3, .duration = 0.10f, .loops = false},
    [ANIMATION_TYPE_HURT_SWORD] = {.count = 3, .duration = 0.10f, .loops = false},

    [ANIMATION_TYPE_IDLE_BARE]  = {.count = 2, .duration = 0.20f, .loops = true},
    [ANIMATION_TYPE_IDLE_BOW]   = {.count = 2, .duration = 0.20f, .loops = true},
    [ANIMATION_TYPE_IDLE_STAFF] = {.count = 2, .duration = 0.20f, .loops = true},
    [ANIMATION_TYPE_IDLE_SWORD] = {.count = 2, .duration = 0.20f, .loops = true},

    [ANIMATION_TYPE_JUMP_BARE]  = {.count = 13, .duration = 0.08f, .loops = false},
    [ANIMATION_TYPE_JUMP_BOW]   = {.count = 13, .duration = 0.08f, .loops = false},
    [ANIMATION_TYPE_JUMP_STAFF] = {.count = 13, .duration = 0.08f, .loops = false},
    [ANIMATION_TYPE_JUMP_SWORD] = {.count = 13, .duration = 0.08f, .loops = false},

    [ANIMATION_TYPE_RUN_BARE]  = {.count = 10, .duration = 0.08f, .loops = true},
    [ANIMATION_TYPE_RUN_BOW]   = {.count = 10, .duration = 0.08f, .loops = true},
    [ANIMATION_TYPE_RUN_STAFF] = {.count = 10, .duration = 0.08f, .loops = true},
    [ANIMATION_TYPE_RUN_SWORD] = {.count = 10, .duration = 0.08f, .loops = true},

    [ANIMATION_TYPE_SHIELD_WALK]            = {.count = 5, .duration = 0.10f, .loops = true},
    [ANIMATION_TYPE_SHIELD_WALK_WITH_SWORD] = {.count = 5, .duration = 0.10f, .loops = true},

    [ANIMATION_TYPE_STAB]       = {.count = 14, .duration = 0.07f, .loops = false},
    [ANIMATION_TYPE_STAFF_CAST] = {.count = 15, .duration = 0.07f, .loops = false},
    [ANIMATION_TYPE_SWIPE]      = {.count = 9, .duration = 0.07f, .loops = false},
    [ANIMATION_TYPE_SWIPE2]     = {.count = 9, .duration = 0.07f, .loops = false},

    [ANIMATION_TYPE_WALK_BARE]  = {.count = 8, .duration = 0.10f, .loops = true},
    [ANIMATION_TYPE_WALK_BOW]   = {.count = 8, .duration = 0.10f, .loops = true},
    [ANIMATION_TYPE_WALK_STAFF] = {.count = 8, .duration = 0.10f, .loops = true},
    [ANIMATION_TYPE_WALK_SWORD] = {.count = 8, .duration = 0.10f, .loops = true},
};

typedef struct {
    AnimationType type;
    int           frame;
    float         frame_timer;
    bool          is_finished;
} Animation;

typedef struct {
    Texture2D bow_shot;
    Texture2D death_bare;
    Texture2D death_bow;
    Texture2D death_staff;
    Texture2D death_sword;
    Texture2D hurt_bare;
    Texture2D hurt_bow;
    Texture2D hurt_staff;
    Texture2D hurt_sword;
    Texture2D idle_bare;
    Texture2D idle_bow;
    Texture2D idle_staff;
    Texture2D idle_sword;
    Texture2D jump_bare;
    Texture2D jump_bow;
    Texture2D jump_staff;
    Texture2D jump_sword;
    Texture2D run_bare;
    Texture2D run_bow;
    Texture2D run_staff;
    Texture2D run_sword;
    Texture2D shield_walk;
    Texture2D shield_walk_with_sword;
    Texture2D stab;
    Texture2D staff_cast;
    Texture2D swipe;
    Texture2D swipe2;
    Texture2D walk_bare;
    Texture2D walk_bow;
    Texture2D walk_staff;
    Texture2D walk_sword;
} AssetManager;

static void asset_manager_init(AssetManager* am) {
    assert(am);

    am->bow_shot = LoadTexture("./assets/bow_shot.png");
    assert(IsTextureValid(am->bow_shot));

    am->death_bare = LoadTexture("./assets/death_bare.png");
    assert(IsTextureValid(am->death_bare));

    am->death_bow = LoadTexture("./assets/death_bow.png");
    assert(IsTextureValid(am->death_bow));

    am->death_staff = LoadTexture("./assets/death_staff.png");
    assert(IsTextureValid(am->death_staff));

    am->death_sword = LoadTexture("./assets/death_sword.png");
    assert(IsTextureValid(am->death_sword));

    am->hurt_bare = LoadTexture("./assets/hurt_bare.png");
    assert(IsTextureValid(am->hurt_bare));

    am->hurt_bow = LoadTexture("./assets/hurt_bow.png");
    assert(IsTextureValid(am->hurt_bow));

    am->hurt_staff = LoadTexture("./assets/hurt_staff.png");
    assert(IsTextureValid(am->hurt_staff));

    am->hurt_sword = LoadTexture("./assets/hurt_sword.png");
    assert(IsTextureValid(am->hurt_sword));

    am->idle_bare = LoadTexture("./assets/idle_bare.png");
    assert(IsTextureValid(am->idle_bare));

    am->idle_bow = LoadTexture("./assets/idle_bow.png");
    assert(IsTextureValid(am->idle_bow));

    am->idle_staff = LoadTexture("./assets/idle_staff.png");
    assert(IsTextureValid(am->idle_staff));

    am->idle_sword = LoadTexture("./assets/idle_sword.png");
    assert(IsTextureValid(am->idle_sword));

    am->jump_bare = LoadTexture("./assets/jump_bare.png");
    assert(IsTextureValid(am->jump_bare));

    am->jump_bow = LoadTexture("./assets/jump_bow.png");
    assert(IsTextureValid(am->jump_bow));

    am->jump_staff = LoadTexture("./assets/jump_staff.png");
    assert(IsTextureValid(am->jump_staff));

    am->jump_sword = LoadTexture("./assets/jump_sword.png");
    assert(IsTextureValid(am->jump_sword));

    am->run_bare = LoadTexture("./assets/run_bare.png");
    assert(IsTextureValid(am->run_bare));

    am->run_bow = LoadTexture("./assets/run_bow.png");
    assert(IsTextureValid(am->run_bow));

    am->run_staff = LoadTexture("./assets/run_staff.png");
    assert(IsTextureValid(am->run_staff));

    am->run_sword = LoadTexture("./assets/run_sword.png");
    assert(IsTextureValid(am->run_sword));

    am->shield_walk = LoadTexture("./assets/shield_walk.png");
    assert(IsTextureValid(am->shield_walk));

    am->shield_walk_with_sword = LoadTexture("./assets/shield_walk_with_sword.png");
    assert(IsTextureValid(am->shield_walk_with_sword));

    am->stab = LoadTexture("./assets/stab.png");
    assert(IsTextureValid(am->stab));

    am->staff_cast = LoadTexture("./assets/staff_cast.png");
    assert(IsTextureValid(am->staff_cast));

    am->swipe = LoadTexture("./assets/swipe.png");
    assert(IsTextureValid(am->swipe));

    am->swipe2 = LoadTexture("./assets/swipe2.png");
    assert(IsTextureValid(am->swipe2));

    am->walk_bare = LoadTexture("./assets/walk_bare.png");
    assert(IsTextureValid(am->walk_bare));

    am->walk_bow = LoadTexture("./assets/walk_bow.png");
    assert(IsTextureValid(am->walk_bow));

    am->walk_staff = LoadTexture("./assets/walk_staff.png");
    assert(IsTextureValid(am->walk_staff));

    am->walk_sword = LoadTexture("./assets/walk_sword.png");
    assert(IsTextureValid(am->walk_sword));
}

static Texture2D asset_manager_get_texture(const AssetManager* am, const int animation_type) {
    assert(am);

    switch (animation_type) {
        case ANIMATION_TYPE_BOW_SHOT:
            return am->bow_shot;
        case ANIMATION_TYPE_DEATH_BARE:
            return am->death_bare;
        case ANIMATION_TYPE_DEATH_BOW:
            return am->death_bow;
        case ANIMATION_TYPE_DEATH_STAFF:
            return am->death_staff;
        case ANIMATION_TYPE_DEATH_SWORD:
            return am->death_sword;
        case ANIMATION_TYPE_HURT_BARE:
            return am->hurt_bare;
        case ANIMATION_TYPE_HURT_BOW:
            return am->hurt_bow;
        case ANIMATION_TYPE_HURT_STAFF:
            return am->hurt_staff;
        case ANIMATION_TYPE_HURT_SWORD:
            return am->hurt_sword;
        case ANIMATION_TYPE_IDLE_BARE:
            return am->idle_bare;
        case ANIMATION_TYPE_IDLE_BOW:
            return am->idle_bow;
        case ANIMATION_TYPE_IDLE_STAFF:
            return am->idle_staff;
        case ANIMATION_TYPE_IDLE_SWORD:
            return am->idle_sword;
        case ANIMATION_TYPE_JUMP_BARE:
            return am->jump_bare;
        case ANIMATION_TYPE_JUMP_BOW:
            return am->jump_bow;
        case ANIMATION_TYPE_JUMP_STAFF:
            return am->jump_staff;
        case ANIMATION_TYPE_JUMP_SWORD:
            return am->jump_sword;
        case ANIMATION_TYPE_RUN_BARE:
            return am->run_bare;
        case ANIMATION_TYPE_RUN_BOW:
            return am->run_bow;
        case ANIMATION_TYPE_RUN_STAFF:
            return am->run_staff;
        case ANIMATION_TYPE_RUN_SWORD:
            return am->run_sword;
        case ANIMATION_TYPE_SHIELD_WALK:
            return am->shield_walk;
        case ANIMATION_TYPE_SHIELD_WALK_WITH_SWORD:
            return am->shield_walk_with_sword;
        case ANIMATION_TYPE_STAB:
            return am->stab;
        case ANIMATION_TYPE_STAFF_CAST:
            return am->staff_cast;
        case ANIMATION_TYPE_SWIPE:
            return am->swipe;
        case ANIMATION_TYPE_SWIPE2:
            return am->swipe2;
        case ANIMATION_TYPE_WALK_BARE:
            return am->walk_bare;
        case ANIMATION_TYPE_WALK_BOW:
            return am->walk_bow;
        case ANIMATION_TYPE_WALK_STAFF:
            return am->walk_staff;
        case ANIMATION_TYPE_WALK_SWORD:
            return am->walk_sword;
        default:
            return am->idle_bare;
    }
}

static void asset_manager_shutdown(AssetManager* am) {
    assert(am);

    UnloadTexture(am->bow_shot);
    UnloadTexture(am->death_bare);
    UnloadTexture(am->death_bow);
    UnloadTexture(am->death_staff);
    UnloadTexture(am->death_sword);
    UnloadTexture(am->hurt_bare);
    UnloadTexture(am->hurt_bow);
    UnloadTexture(am->hurt_staff);
    UnloadTexture(am->hurt_sword);
    UnloadTexture(am->idle_bare);
    UnloadTexture(am->idle_bow);
    UnloadTexture(am->idle_staff);
    UnloadTexture(am->idle_sword);
    UnloadTexture(am->jump_bare);
    UnloadTexture(am->jump_bow);
    UnloadTexture(am->jump_staff);
    UnloadTexture(am->jump_sword);
    UnloadTexture(am->run_bare);
    UnloadTexture(am->run_bow);
    UnloadTexture(am->run_staff);
    UnloadTexture(am->run_sword);
    UnloadTexture(am->shield_walk);
    UnloadTexture(am->shield_walk_with_sword);
    UnloadTexture(am->stab);
    UnloadTexture(am->staff_cast);
    UnloadTexture(am->swipe);
    UnloadTexture(am->swipe2);
    UnloadTexture(am->walk_bare);
    UnloadTexture(am->walk_bow);
    UnloadTexture(am->walk_staff);
    UnloadTexture(am->walk_sword);
}

typedef enum {
    PLAYER_STATE_DEATH,
    PLAYER_STATE_HURT,
    PLAYER_STATE_IDLE,
    PLAYER_STATE_JUMP,
    PLAYER_STATE_RUN,
    PLAYER_STATE_ATTACK,
    PLAYER_STATE_WALK,

    PLAYER_STATE_MAX,
} PlayerState;

typedef struct {
    const AssetManager* asset_manager;

    PlayerState current_state;
    PlayerState prev_state;

    Rectangle source;
    Rectangle dest;
    Vector2   origin;
    float     rotation;
    Color     tint;

    Animation animation;
} Player;

static void player_init(Player* player, const AssetManager* asset_manager) {
    assert(player);

    player->asset_manager = asset_manager;

    player->current_state = PLAYER_STATE_IDLE;
    player->prev_state    = PLAYER_STATE_IDLE;

    player->source = (Rectangle){};
    player->dest   = (Rectangle){};
    player->source = (Rectangle){};

    player->animation = (Animation){
        .type        = ANIMATION_TYPE_IDLE_BARE,
        .frame       = 0,
        .frame_timer = 0.0f,
        .is_finished = false,
    };
}

static void player_animate(Player* player, const float dt) {
    assert(player);
}

static void player_update(Player* player, const float dt) {
    assert(player);
}

static void player_draw(const Player* player) {
    assert(player);

    const Texture2D texture
        = asset_manager_get_texture(player->asset_manager, player->animation.type);
    DrawTexturePro(
        texture, player->source, player->dest, player->origin, player->rotation, player->tint);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation Test");

    AssetManager asset_manager;
    asset_manager_init(&asset_manager);

    Player player;
    player_init(&player, &asset_manager);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        player_update(&player, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        player_draw(&player);

        EndDrawing();
    }

    asset_manager_shutdown(&asset_manager);

    CloseWindow();

    return 0;
}
