#include <stdio.h>
#include <stdlib.h>

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_EXPLORE,
    GAME_STATE_SHOP,
    GAME_STATE_EXIT,
} GameState;

typedef struct {
    int max_hp;
    int hp;
    int damage;
} Entity;

int main(void) {
    GameState current_state = GAME_STATE_MENU;

    Entity player = {.max_hp = 100, .hp = 100, .damage = 5};

    switch (current_state) {
        case GAME_STATE_MENU: {
            while (current_state == GAME_STATE_MENU) {
                system("clear");

                printf("\nSimple Arpg\n");
                printf("1) Explore\n");
                printf("2) Shop\n");
                printf("3) Exit\n");
                printf("> ");
                char input = fgetc(stdin);
                switch (input) {
                    case '1':
                        current_state = GAME_STATE_EXPLORE;
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

        case GAME_STATE_EXPLORE: {
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
