#include <stdio.h>
#include <stdlib.h>

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_FIGHT,
    GAME_STATE_SHOP,
    GAME_STATE_EXIT,
} GameState;

typedef struct {
    const char* name;
    int         base_hp;
    int         base_damage;
    int         base_defense;
} Entity;

typedef enum {
    ENEMY_TYPE_GOBLIN,
    ENEMY_TYPE_ORC,
    ENEMY_TYPE_SLIME,
    ENEMY_TYPE_SKELETON,
    ENEMY_TYPE_DRAGON,
    ENEMY_TYPE_MAX,
} EnemyType;

static const Entity enemies[5] = {{"Goblin", 30, 8, 3},
                                  {"Orc", 50, 12, 5},
                                  {"Slime", 25, 6, 8},
                                  {"Skeleton", 40, 10, 4},
                                  {"Dragon", 100, 20, 10}};

int main(void) {
    GameState current_state = GAME_STATE_MENU;

    Entity player = (Entity){"Player", 100, 20, 10};

    switch (current_state) {
        case GAME_STATE_MENU: {
            while (current_state == GAME_STATE_MENU) {
                system("clear");

                printf("\nSimple Arpg\n");
                printf("[1] Fight\n");
                printf("[2] Shop\n");
                printf("[3] Exit\n");
                printf("> ");
                char input = fgetc(stdin);
                switch (input) {
                    case '1':
                        current_state = GAME_STATE_FIGHT;
                        break;
                    case '2':
                        current_state = GAME_STATE_SHOP;
                        break;
                    case '3':
                        current_state = GAME_STATE_EXIT;
                        break;
                    default:
                        printf("Invalid input\n");
                        printf("Press enter to continue ...\n");
                        getchar();
                        break;
                }
            }
        } break;

        case GAME_STATE_FIGHT: {
            while (current_state == GAME_STATE_FIGHT) {
            }
        } break;

        case GAME_STATE_SHOP: {
        } break;

        case GAME_STATE_EXIT: {
            printf("Thanks for playing\n");
            return 0;
        } break;
    }

    return 0;
}
