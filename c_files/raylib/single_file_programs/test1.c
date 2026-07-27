#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef enum BulletType{
    TYPE_MAGIC_MISSILES,
}BulletType;

typedef struct Bullet{
    Vector2 center;
    float radius;
    float speed;
    Vector2 direction;
}Bullet;

typedef struct BulletConfing{

}BulletConfing;

static void bullet_init(Bullet* bullet);
static void bullet_update(Bullet* bullet, const float dt);
static void bullet_draw(const Bullet* bullet);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
