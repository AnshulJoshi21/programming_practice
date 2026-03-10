#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM_INT(min, max) ((min) + rand() % (max - min + 1))

static bool get_user_input(long *user_input)
{
    char buffer[100];
    char *end_ptr;
    long value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return false;

    errno = 0;
    value = strtol(buffer, &end_ptr, 10);

    if (errno == ERANGE)
        return false;
    else if (end_ptr == buffer)
        return false;

    *user_input = value;

    return true;
}

int main(void)
{
    srand((unsigned int)time(NULL));

    printf("I am thinking of a number between 1 and 100\n");
    const int random_int = RANDOM_INT(1, 100);

    long user_input;

    while (true) {
        printf("Guess the number: ");

        if (get_user_input(&user_input)) {
            if (user_input == random_int) {
                printf("Correct\n");
                break;
            } else if (user_input < random_int) {
                printf("too low, try again\n");
            } else if (user_input > random_int) {
                printf("too high, try again\n");
            }
        } else {
            printf("invalid input, try again\n");
        }
    }
    return 0;
}
