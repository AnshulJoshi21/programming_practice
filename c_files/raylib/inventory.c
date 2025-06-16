#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5
#define SLOT_SIZE 100
#define SLOT_GAP 5

#define NUM_OF_ITEMS 5

typedef struct Item
{
  int id;
  Rectangle rect;
  Color color;
  Vector2 offset;
  bool is_dragging;

} Item;

void
item_init(Item* item, int id, float y)
{
  item->id = id;
  item->rect = (Rectangle){ GetScreenWidth() - 200, y, 60, 60 };
  item->color = (Color){
    GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255
  };
  item->is_dragging = false;
  item->offset = (Vector2){ 0, 0 };
}

void
item_draw(Item* item)
{
  DrawRectangleRec(item->rect, item->color);
}

int
main(void)
{
  const int SCREEN_WIDTH = 1000;
  const int SCREEN_HEIGHT = 800;
  const char SCREEN_TITLE[] = "Inventory";
  const Color SCREEN_BACKGROUND = RAYWHITE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  Vector2 position = (Vector2){ 10, 10 };
  Item empty_item = { 0 };

  float last_current_time = 0.0f;
  float interval = 1.0f;

  Rectangle slots[ROWS * COLS];
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int x = j * (SLOT_SIZE + SLOT_GAP) + position.x;
      int y = i * (SLOT_SIZE + SLOT_GAP) + position.y;

      slots[i * COLS + j] = (Rectangle){ x, y, SLOT_SIZE, SLOT_SIZE };
    }
  }

  Item inventory[ROWS * COLS];
  int inventory_size = 0;
  bool show_inventory = true;

  Item item_list[NUM_OF_ITEMS];
  int item_list_size = NUM_OF_ITEMS;

  for (int i = 0; i < item_list_size; i++) {
    Item item;
    item_init(&item, (i + 1), (i + 1) * SLOT_SIZE);

    item_list[i] = item;
  }

  while (!WindowShouldClose()) {

    // show inventory
    if (IsKeyPressed(KEY_I)) {
      show_inventory = !show_inventory;
    }

    Vector2 mouse_pos = GetMousePosition();

    // drag items from inventory
    for (int i = 0; i < inventory_size; i++) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
          CheckCollisionPointRec(mouse_pos, inventory[i].rect)) {

        inventory[i].is_dragging = true;
        inventory[i].offset.x = mouse_pos.x - inventory[i].rect.x;
        inventory[i].offset.y = mouse_pos.y - inventory[i].rect.y;

        // add item to item_list
        item_list[item_list_size] = inventory[i];
        item_list_size++;

        // remove item from inventory
        inventory[i] = inventory[inventory_size - 1];
        inventory[inventory_size - 1] = empty_item;
        inventory_size--;
        break;
      }
    }

    // handle items in item_list (drag, drop, remove)
    for (int i = 0; i < item_list_size; i++) {
      Item* current_item = &item_list[i];

      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
          (CheckCollisionPointRec(mouse_pos, current_item->rect))) {
        current_item->is_dragging = true;
        current_item->offset.x = mouse_pos.x - current_item->rect.x;
        current_item->offset.y = mouse_pos.y - current_item->rect.y;
      }

      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && current_item->is_dragging) {
        current_item->rect.x = mouse_pos.x - current_item->offset.x;
        current_item->rect.y = mouse_pos.y - current_item->offset.y;
      }

      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) &&
          current_item->is_dragging) {

        current_item->is_dragging = false;

        for (int j = 0; j < ROWS * COLS; j++) {
          if (CheckCollisionRecs(current_item->rect, slots[j])) {
            // snap item to slot
            current_item->rect.x =
              slots[j].x + (slots[j].width - current_item->rect.width) / 2;
            current_item->rect.y =
              slots[j].y + (slots[j].height - current_item->rect.height) / 2;

            // add item to inventory
            inventory[inventory_size] = item_list[i];
            inventory_size++;

            // remove item from item_list
            item_list[i] = item_list[item_list_size - 1];
            item_list[item_list_size - 1] = empty_item;
            item_list_size--;
            break;
          }
        }
      }
    }

    // checks

    float current_time = GetTime();
    if (current_time - last_current_time >= interval) {
      last_current_time = current_time;

      system("clear");

      for (int i = 0; i < inventory_size; i++) {
        printf("INVENTORY\n");
        printf("ID: %d, POSITION: (%0.2f, %0.2f)\n",
               inventory[i].id,
               inventory[i].rect.x,
               inventory[i].rect.y);
      }

      for (int i = 0; i < NUM_OF_ITEMS; i++) {
        printf("ITEM LIST\n");
        printf("ID: %d, POSITION: (%0.2f, %0.2f)\n",
               item_list[i].id,
               item_list[i].rect.x,
               item_list[i].rect.y);
      }
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    if (show_inventory) {
      // draw inventory slots
      for (int i = 0; i < ROWS * COLS; i++) {
        Color color = CheckCollisionPointRec(mouse_pos, slots[i]) ? RED : BLACK;

        DrawRectangleLinesEx(slots[i], 5.0, color);
      }

      // draw inventory items
      for (int i = 0; i < inventory_size; i++) {
        item_draw(&inventory[i]);
      }
    }

    // draw items list (items outside inventory)
    for (int i = 0; i < item_list_size; i++) {
      item_draw(&item_list[i]);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}