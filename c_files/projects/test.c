#include <stdbool.h>
#include <stdio.h>

typedef enum GameState {
    ST_MAIN_MENU,
    ST_CHARACTER_CREATION,
    ST_EXPLORE,
    ST_TOWN,
    ST_QUIT

} GameState;

typedef enum CharacterType {
    CT_WARRIOR,
    CT_MAGE,
    CT_RANGER,
    CT_ROGUE

} CharacterType;

typedef enum 

    static void
    main_menu(GameState *current_state)
{
    int command;

    printf("\nDUNGEON DELVE\n\n");
    printf("1. New Game\n");
    printf("2. Quit\n\n");

    bool running = true;

    while (running) {
        printf("> ");
        scanf("%d", &command);

        switch (command) {
        case 1:
            *current_state = ST_CHARACTER_CREATION;
            running        = false;
            break;
        case 2:
            *current_state = ST_QUIT;
            running        = false;
            break;

        default:
            printf("Invalid input\n");
            break;
        }
    }
}

int main(void)
{
    GameState current_state = ST_MAIN_MENU;

    bool running = true;

    while (running) {
        switch (current_state) {
        case ST_MAIN_MENU:
            main_menu(&current_state);
            break;
        case ST_CHARACTER_CREATION:
            break;
        case ST_EXPLORE:
            break;
        case ST_TOWN:
            break;
        case ST_QUIT:
            running = false;
            break;

        default:
            running = false;
            break;
        }
    }

    return 0;
}
