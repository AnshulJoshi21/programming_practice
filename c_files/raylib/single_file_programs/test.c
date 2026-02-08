#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

// -- CONSTANTS --
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_STACK 10
#define INITIAL_CAPACITY 4

// -- DATA STRUCTURES --
typedef struct {
    int id;
    const char *name;
} ItemData;

static const ItemData ITEM_DB[] = {
    {0, "SWORD"}, {1, "HELMET"}, {2, "POTION"}
};

typedef struct {
    int id;
    int count;
    Rectangle rect;
} Item;

typedef struct {
    Item *items;
    int size;
    int capacity;
} Inventory;

typedef enum { SRC_NONE, SRC_WORLD, SRC_PLAYER } DragSource;

typedef struct {
    DragSource source;
    int index;
    bool active;
    Vector2 offset;
} DragState;

// -- INVENTORY CORE --
void Inv_Init(Inventory *inv) {
    inv->size = 0;
    inv->capacity = INITIAL_CAPACITY;
    inv->items = malloc(inv->capacity * sizeof(Item));
}

void Inv_Add(Inventory *inv, Item item) {
    if (inv->size >= inv->capacity) {
        inv->capacity *= 2;
        inv->items = realloc(inv->items, inv->capacity * sizeof(Item));
    }
    inv->items[inv->size++] = item;
}

void Inv_Remove(Inventory *inv, int index) {
    if (index < 0 || index >= inv->size) return;
    for (int i = index; i < inv->size - 1; i++) {
        inv->items[i] = inv->items[i + 1];
    }
    inv->size--;
}

// -- HELPER: UI & RENDERING --
void DrawItem(Item item, Color color) {
    DrawRectangleLinesEx(item.rect, 2.0f, color);
    // Assuming center_and_draw_text is in your utils.h
    // Replace with DrawText for this standalone example:
    DrawText(ITEM_DB[item.id].name, item.rect.x + 5, item.rect.y + 5, 10, color);
}

// -- MAIN --
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Inventory System - Refactored");
    SetTargetFPS(60);

    // Layout Settings
    const float slotSize = 80.0f;
    const float gap = 15.0f;
    const int rows = 2, cols = 5;

    Inventory worldInv, playerInv;
    Inv_Init(&worldInv);
    Inv_Init(&playerInv);

    Rectangle slots[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
        slots[i] = (Rectangle){
            160.0f + (i % cols) * (slotSize + gap),
            50.0f + (i / cols) * (slotSize + gap),
            slotSize, slotSize
        };
    }

    Rectangle spawner = { SCREEN_WIDTH/2 - 40, SCREEN_HEIGHT - 120, 80, 80 };
    DragState drag = { .source = SRC_NONE, .active = false };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        // --- UPDATE ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // 1. Check Spawner
            if (CheckCollisionPointRec(mouse, spawner)) {
                Item newItem = { 
                    .id = GetRandomValue(0, 2), 
                    .count = 1, 
                    .rect = { spawner.x + 10, spawner.y + 10, 60, 60 } 
                };
                Inv_Add(&worldInv, newItem);
                drag = (DragState){ SRC_WORLD, worldInv.size - 1, true, 
                                   { mouse.x - newItem.rect.x, mouse.y - newItem.rect.y } };
            }
            // 2. Check Player Inventory (to drop back to world)
            else {
                for (int i = 0; i < playerInv.size; i++) {
                    if (CheckCollisionPointRec(mouse, playerInv.items[i].rect)) {
                        Item item = playerInv.items[i];
                        Inv_Remove(&playerInv, i);
                        Inv_Add(&worldInv, item);
                        drag = (DragState){ SRC_WORLD, worldInv.size - 1, true, 
                                           { mouse.x - item.rect.x, mouse.y - item.rect.y } };
                        break;
                    }
                }
            }
            // 3. Check World Items (to pick up)
            if (!drag.active) {
                for (int i = 0; i < worldInv.size; i++) {
                    if (CheckCollisionPointRec(mouse, worldInv.items[i].rect)) {
                        drag = (DragState){ SRC_WORLD, i, true, 
                                           { mouse.x - worldInv.items[i].rect.x, mouse.y - worldInv.items[i].rect.y } };
                        break;
                    }
                }
            }
        }

        if (drag.active) {
            worldInv.items[drag.index].rect.x = mouse.x - drag.offset.x;
            worldInv.items[drag.index].rect.y = mouse.y - drag.offset.y;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                bool placed = false;
                for (int i = 0; i < rows * cols; i++) {
                    if (CheckCollisionPointRec(mouse, slots[i])) {
                        Item item = worldInv.items[drag.index];
                        item.rect = (Rectangle){ slots[i].x + 10, slots[i].y + 10, 60, 60 };
                        Inv_Add(&playerInv, item);
                        Inv_Remove(&worldInv, drag.index);
                        placed = true;
                        break;
                    }
                }
                drag.active = false;
            }
        }

        // --- DRAW ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < rows * cols; i++) DrawRectangleLinesEx(slots[i], 3, BLACK);
        DrawRectangleLinesEx(spawner, 3, GRAY);
        DrawText("SPAWN", spawner.x + 15, spawner.y + 30, 15, GRAY);

        for (int i = 0; i < playerInv.size; i++) DrawItem(playerInv.items[i], BLUE);
        for (int i = 0; i < worldInv.size; i++) DrawItem(worldInv.items[i], DARKGREEN);

        DrawText(TextFormat("Player Items: %d", playerInv.size), 10, 570, 20, DARKGRAY);
        EndDrawing();
    }

    free(worldInv.items);
    free(playerInv.items);
    CloseWindow();
    return 0;
}
