#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

static const int SCREEN_SIZE = 800;
static const int MARGIN      = 100;
#define GRID_SIZE 20
static const int BLOCK_SIZE = (SCREEN_SIZE - (MARGIN * 2)) / GRID_SIZE;

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
    int x;
    int y;
} Point;

typedef struct Node {
    Point        data;
    struct Node* next;
} Node;

static Node* create_node(const Point data) {
    Node* new_node = malloc(sizeof(Node));
    assert(new_node);
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

typedef struct {
    Node* head;
    int   size;
} LinkedList;

static void ll_init(LinkedList* ll) {
    assert(ll);

    ll->head = NULL;
    ll->size = 0;
}

static const Node* ll_get_tail(const LinkedList* ll) {
    assert(ll);

    const Node* current = ll->head;
    while (current->next) {
        current = current->next;
    }

    return current;
}

static void ll_prepend(LinkedList* ll, const Point data) {
    assert(ll);

    Node* new_node = create_node(data);
    new_node->next = ll->head;
    ll->head       = new_node;
    ll->size++;
}

static void ll_append(LinkedList* ll, const Point data) {
    assert(ll);

    Node* new_node = create_node(data);

    if (!ll->head) {
        ll->head = new_node;
        ll->size++;
        return;
    }

    Node* current = ll->head;
    while (current->next) {
        current = current->next;
    }

    current->next = new_node;
    ll->size++;
}

static void ll_pop(LinkedList* ll) {
    assert(ll);

    if (!ll->head) {
        return;
    }

    if (!ll->head->next) {
        ll->head = NULL;
        ll->size--;
        return;
    }

    Node* prev    = NULL;
    Node* current = ll->head;

    while (current->next) {
        prev    = current;
        current = current->next;
    }

    free(current);
    prev->next = NULL;
    ll->size--;
}

static void ll_free(LinkedList* ll) {
    assert(ll);

    Node* current = ll->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    ll->size = 0;
}

typedef enum {
    RIGHT,
    LEFT,
    UP,
    DOWN,
} Direction;

typedef struct {
    Point      temp_head;
    Direction  direction;
    LinkedList body;

    float elapsed_time;
    float move_interval;
} Snake;

static void snake_init(Snake* snake) {
    assert(snake);

    snake->temp_head = (Point){MARGIN, MARGIN};
    snake->direction = RIGHT;

    ll_init(&snake->body);
    ll_append(&snake->body, snake->temp_head);

    snake->elapsed_time  = 0.0f;
    snake->move_interval = 0.09f;
}

static void snake_handle_input(Snake* snake) {
    assert(snake);

    if (IsKeyPressed(KEY_D) && snake->direction != LEFT) {
        snake->direction = RIGHT;
    }
    if (IsKeyPressed(KEY_A) && snake->direction != RIGHT) {
        snake->direction = LEFT;
    }
    if (IsKeyPressed(KEY_W) && snake->direction != DOWN) {
        snake->direction = UP;
    }
    if (IsKeyPressed(KEY_S) && snake->direction != UP) {
        snake->direction = DOWN;
    }
}

static void snake_move(Snake* snake) {
    assert(snake);

    switch (snake->direction) {
        case RIGHT:
            snake->temp_head.x += BLOCK_SIZE;
            break;
        case LEFT:
            snake->temp_head.x -= BLOCK_SIZE;
            break;
        case UP:
            snake->temp_head.y -= BLOCK_SIZE;
            break;
        case DOWN:
            snake->temp_head.y += BLOCK_SIZE;
            break;
        default:
            return;
    }
}

static bool snake_collision_walls(const Snake* snake) {
    assert(snake);

    return snake->temp_head.x < MARGIN || snake->temp_head.x > SCREEN_SIZE - MARGIN - BLOCK_SIZE
           || snake->temp_head.y < MARGIN || snake->temp_head.y > SCREEN_SIZE - MARGIN - BLOCK_SIZE;
}

static bool snake_collision_itself(const Snake* snake) {
    assert(snake);

    const Node* current = snake->body.head;
    for (int i = 0; i < snake->body.size; i++) {
        if (current->data.x == snake->temp_head.x && current->data.y == snake->temp_head.y) {
            return true;
        }

        current = current->next;
    }

    return false;
}

static bool snake_update(Snake* snake, const float dt) {
    assert(snake);

    snake_handle_input(snake);

    snake->elapsed_time += dt;
    if (snake->elapsed_time >= snake->move_interval) {
        snake->elapsed_time = 0.0f;

        snake_move(snake);

        if (snake_collision_itself(snake) || snake_collision_walls(snake)) {
            return true;
        }

        ll_prepend(&snake->body, snake->temp_head);
        ll_pop(&snake->body);
    }

    return false;
}

static void snake_draw(const Snake* snake) {
    assert(snake);

    const Node* current = snake->body.head;
    for (int i = 0; i < snake->body.size; i++) {
        const Color color = (i == 0) ? BLUE : SKYBLUE;
        DrawRectangle(current->data.x, current->data.y, BLOCK_SIZE, BLOCK_SIZE, color);

        current = current->next;
    }
}

typedef struct {
    const Snake* snake;
    Point        pos;
    Color        color;
} Food;

static void food_gen_random(Food* food) {
    assert(food);

    for (int i = 0; i < 10000; i++) {
        const int random_x = GetRandomValue(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN;
        const int random_y = GetRandomValue(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN;

        bool        snake_collision = false;
        const Node* current         = food->snake->body.head;
        for (int n = 0; n < food->snake->body.size; n++) {
            if (current->data.x == random_x && current->data.y == random_y) {
                snake_collision = true;
                break;
            }

            current = current->next;
        }

        if (!snake_collision) {
            food->pos.x = random_x;
            food->pos.y = random_y;
            return;
        }
    }
}

static void food_init(Food* food, const Snake* snake) {
    assert(food);

    food->snake = snake;
    food->color = RED;
    food_gen_random(food);
}

static void food_draw(const Food* food) {
    assert(food);

    DrawRectangle(food->pos.x, food->pos.y, BLOCK_SIZE, BLOCK_SIZE, food->color);
}

static void draw_grid(void) {
    const float thickness = 2.0f;
    const Color color     = LIGHTGRAY;

    for (float x = MARGIN + BLOCK_SIZE; x < SCREEN_SIZE - MARGIN; x += BLOCK_SIZE) {
        DrawLineEx((Vector2){x, MARGIN}, (Vector2){x, SCREEN_SIZE - MARGIN}, thickness, color);
    }

    for (float y = MARGIN + BLOCK_SIZE; y < SCREEN_SIZE - MARGIN; y += BLOCK_SIZE) {
        DrawLineEx((Vector2){MARGIN, y}, (Vector2){SCREEN_SIZE - MARGIN, y}, thickness, color);
    }

    // draw outline rect
    DrawRectangleLinesEx(
        (Rectangle){MARGIN, MARGIN, SCREEN_SIZE - (MARGIN * 2), SCREEN_SIZE - (MARGIN * 2)},
        5.0f,
        GRAY);
}

int main(void) {
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Snake");
    SetTargetFPS(60);

    int  score     = 0;
    bool game_over = false;

    Snake snake;
    snake_init(&snake);

    Food food;
    food_init(&food, &snake);

    while (!WindowShouldClose()) {
        if (!game_over) {
            const float dt = GetFrameTime();

            game_over = snake_update(&snake, dt);

            // snake collision food
            const Node* snake_tail = ll_get_tail(&snake.body);
            const Node* snake_head = snake.body.head;
            if (snake_head->data.x == food.pos.x && snake_head->data.y == food.pos.y) {
                ll_append(&snake.body, snake_tail->data);
                food_gen_random(&food);
                score++;
            }

        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                score     = 0;
                game_over = false;

                snake_init(&snake);
                food_init(&food, &snake);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // draw score
        draw_centered_text(
            TextFormat("Score: %d", score), (Rectangle){0, 0, GetScreenWidth(), MARGIN}, 20.0f);

        food_draw(&food);
        snake_draw(&snake);

        draw_grid();

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

        EndDrawing();
    }

    ll_free(&snake.body);

    CloseWindow();

    return 0;
}
