#include "utils.h"

#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

//-- CONSTANTS ---------------------------------------//
static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 600;

static const int INV_ROWS  = 2;
static const int INV_COLS  = 5;
static const int MAX_INV   = INV_ROWS * INV_COLS;
static const int MAX_STACK = 10;

static const float SLOT_GAP = 10.0f;

static const float MARGIN_TOP        = 50.0f;
static const float MARGIN_HORIZONTAL = 170.0f;

static const int INITIAL_CAPACITY = 4;
static const int GROWTH_FACTOR    = 2;
static const int SHRINK_FACTOR    = 4;

//-- ITEM DATABASE ---------------------------------------//
typedef enum ItemType {
    IT_WEAPON,
    IT_ARMOUR,
    IT_CONSUMABLE

} ItemType;

typedef struct ItemData
{
    const int id;
    const ItemType type;
    const char *name;

} ItemData;

static const ItemData item_db[] = {{0, IT_WEAPON, "SWORD"},
                                   {1, IT_ARMOUR, "HELMET"},
                                   {2, IT_CONSUMABLE, "POTION"}};

static const int item_db_size = sizeof(item_db) / sizeof(item_db[0]);

//-- INVENTORY ---------------------------------------//
typedef struct Item
{
    int id;
    int count;
    Rectangle rect;

} Item;

typedef struct Inventory
{
    Item *items;
    int size;
    int capacity;

} Inventory;

static void inv_init(Inventory *inv)
{
    assert(inv);

    inv->size     = 0;
    inv->capacity = INITIAL_CAPACITY;

    inv->items = malloc(inv->capacity * sizeof(Item));
    assert(inv->items);
}

static void inv_adjust_capacity(Inventory *inv)
{
    assert(inv);

    // grow
    if (inv->size >= inv->capacity) {
        inv->capacity *= GROWTH_FACTOR;
    }
    // shrink
    else if (inv->size * SHRINK_FACTOR < inv->capacity) {
        inv->capacity /= GROWTH_FACTOR;

        if (inv->capacity < INITIAL_CAPACITY) {
            inv->capacity = INITIAL_CAPACITY;
        }
    }
    // do nothing
    else
        return;

    Item *temp = realloc(inv->items, inv->capacity * sizeof(Item));
    assert(temp);

    inv->items = temp;
}

static void inv_append(Inventory *inv, Item item)
{
    assert(inv);

    inv_adjust_capacity(inv);

    inv->items[inv->size++] = item;
}

static void inv_remove(Inventory *inv, int index)
{
    assert(inv);
    assert(index < inv->size && index >= 0);

    for (int i = index; i < inv->size - 1; i++) {
        inv->items[i] = inv->items[i + 1];
    }

    inv->size--;
    inv_adjust_capacity(inv);
}

static void inv_free(Inventory *inv)
{
    if (inv->items) {
        free(inv->items);
        inv->items = NULL;

        inv->size = inv->capacity = 0;
    }
}

//-- MISC ---------------------------------------//
static float get_slot_size(void)
{
    // horizontal
    float total_gap       = SLOT_GAP * (INV_COLS - 1); // remove trailing gap
    float total_margin    = MARGIN_HORIZONTAL * 2;
    float available_width = GetScreenWidth() - total_margin - total_gap;

    return available_width / INV_COLS;
}

//-- DRAGGING ---------------------------------------//
typedef enum DragSource {
    D_WORLD_INV,
    D_PLAYER_INV,
    D_NONE

} DragSource;

typedef struct DragState
{
    int index;
    DragSource source;
    bool active;
    Vector2 offset;

} DragState;

//-- MAIN ---------------------------------------//
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Inventory Test");
    SetTargetFPS(60);

    float slot_size      = get_slot_size();
    float slot_thickness = 5.0f;
    Color slot_color     = BLACK;

    float item_size      = slot_size - (slot_size / 4);
    float item_thickness = 2.0f;
    Color item_color     = BLUE;

    // inventory slots
    Rectangle slots[MAX_INV];
    for (int i = 0; i < MAX_INV; i++) {
        float x = (i % INV_COLS) * (slot_size + SLOT_GAP) + MARGIN_HORIZONTAL;
        float y = (i / INV_COLS) * (slot_size + SLOT_GAP) + MARGIN_TOP;

        slots[i] = (Rectangle){x, y, slot_size, slot_size};
    }

    // item spawner
    Rectangle spawner_rect =
        (Rectangle){GetScreenWidth() / 2.0f - slot_size / 2.0f,
                    GetScreenHeight() - slot_size * 2, slot_size, slot_size};
    Color spawner_color = GRAY;

    // inventories
    Inventory player_inv;
    inv_init(&player_inv);

    Inventory world_inv;
    inv_init(&world_inv);

    // dragging
    DragState drag_state = {
        .index = -1, .source = D_NONE, .active = false, .offset = {0}};

    while (!WindowShouldClose()) {
        // UPDATE
        Vector2 mouse_pos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // spawn item
            if (CheckCollisionPointRec(mouse_pos, spawner_rect)) {
                float item_x  = spawner_rect.x + (slot_size - item_size) / 2.0f;
                float item_y  = spawner_rect.y + (slot_size - item_size) / 2.0f;
                Item new_item = (Item){
                    .id    = GetRandomValue(0, item_db_size - 1),
                    .count = 1,
                    .rect  = (Rectangle){item_x, item_y, item_size, item_size}};

                inv_append(&world_inv, new_item);
                drag_state.index  = world_inv.size - 1;
                drag_state.source = D_WORLD_INV;
                drag_state.active = true;
                drag_state.offset = (Vector2){
                    mouse_pos.x - world_inv.items[drag_state.index].rect.x,
                    mouse_pos.y - world_inv.items[drag_state.index].rect.y,
                };
            }
            // remove from player inventory
            else {
                for (int i = 0; i < player_inv.size; i++) {
                    if (CheckCollisionPointRec(mouse_pos,
                                               player_inv.items[i].rect)) {
                        //
                        inv_append(&world_inv, player_inv.items[i]);
                        inv_remove(&player_inv, i);

                        drag_state.index  = world_inv.size - 1;
                        drag_state.source = D_WORLD_INV;
                        drag_state.active = true;
                        drag_state.offset = (Vector2){
                            mouse_pos.x -
                                world_inv.items[drag_state.index].rect.x,
                            mouse_pos.y -
                                world_inv.items[drag_state.index].rect.y,
                        };

                        break;
                    }
                }
            }

            // re-drag world_inv item
            if (!drag_state.active) {
                for (int i = 0; i < world_inv.size; i++) {
                    if (CheckCollisionPointRec(mouse_pos,
                                               world_inv.items[i].rect)) {

                        drag_state.index  = i;
                        drag_state.source = D_WORLD_INV;
                        drag_state.active = true;
                        drag_state.offset = (Vector2){
                            mouse_pos.x -
                                world_inv.items[drag_state.index].rect.x,
                            mouse_pos.y -
                                world_inv.items[drag_state.index].rect.y,
                        };

                        break;
                    }
                }
            }
        }

        // dragging item
        if (drag_state.active) {
            world_inv.items[drag_state.index].rect.x =
                mouse_pos.x - drag_state.offset.x;
            world_inv.items[drag_state.index].rect.y =
                mouse_pos.y - drag_state.offset.y;

            // dropping item
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                for (int i = 0; i < MAX_INV; i++) {
                    if (CheckCollisionPointRec(mouse_pos, slots[i])) {

                        world_inv.items[drag_state.index].rect.x =
                            slots[i].x + (slot_size - item_size) / 2.0f;
                        world_inv.items[drag_state.index].rect.y =
                            slots[i].y + (slot_size - item_size) / 2.0f;

                        inv_append(&player_inv,
                                   world_inv.items[drag_state.index]);
                        inv_remove(&world_inv, drag_state.index);

                        break;
                    }
                }

                // reset drag_state
                drag_state = (DragState){.index  = -1,
                                         .source = D_NONE,
                                         .active = false,
                                         .offset = {0}};
            }
        }

        // DRAW
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // draw slots
        for (int i = 0; i < MAX_INV; i++) {
            DrawRectangleLinesEx(slots[i], slot_thickness, slot_color);
        }

        // draw spawner
        DrawRectangleLinesEx(spawner_rect, slot_thickness, spawner_color);
        center_and_draw_text("SPAWNER", 10.0f, 2.0f, spawner_rect,
                             spawner_color);

        // draw inventories
        // world
        for (int i = 0; i < world_inv.size; i++) {
            DrawRectangleLinesEx(world_inv.items[i].rect, item_thickness,
                                 item_color);
            center_and_draw_text(item_db[world_inv.items[i].id].name, 10.0f,
                                 2.0f, world_inv.items[i].rect, item_color);
            center_and_draw_text(TextFormat("x%d", world_inv.items[i].count),
                                 10.0f, 2.0f,
                                 (Rectangle){world_inv.items[i].rect.x,
                                             world_inv.items[i].rect.y,
                                             item_size, item_size + 20.0f},
                                 BLACK);
        }
        // player
        for (int i = 0; i < player_inv.size; i++) {
            DrawRectangleLinesEx(player_inv.items[i].rect, item_thickness,
                                 item_color);
            center_and_draw_text(item_db[player_inv.items[i].id].name, 10.0f,
                                 2.0f, player_inv.items[i].rect, item_color);
            center_and_draw_text(TextFormat("x%d", player_inv.items[i].count),
                                 10.0f, 2.0f,
                                 (Rectangle){player_inv.items[i].rect.x,
                                             player_inv.items[i].rect.y,
                                             item_size, item_size + 20.0f},
                                 BLACK);
        }

        // draw inventory size
        DrawText(TextFormat("world inv size: %d", world_inv.size), 20,
                 GetScreenHeight() - 140, 20, BLACK);
        DrawText(TextFormat("player inv size: %d", player_inv.size), 20,
                 GetScreenHeight() - 100, 20, BLACK);

        EndDrawing();
    }

    // free inventories
    inv_free(&world_inv);
    inv_free(&player_inv);

    CloseWindow();

    return 0;
}
