#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    false;

    *user_input = value;

    return true;
}

int main(void)
{
    long user_input = -1;
    long num1, num2;

    while (user_input != 5) {

        system("clear");

        printf("Calculator\n\n");

        printf("1) Addition\n");
        printf("2) Substraction\n");
        printf("3) Multiplication\n");
        printf("4) Division\n");
        printf("5) QUIT\n\n");

        printf("> ");

        if (get_user_input(&user_input)) {
            switch (user_input) {
            case 1:
                printf("Num1: ");
                if (get_user_input(&num1)) {
                    printf("Num2: ");
                    if (get_user_input(&num2)) {
                        printf("\n%lu + %lu = %lu\n", num1, num2, num1 + num2);
                        getchar();
                    }
                }
                break;
            case 2:
                printf("Num1: ");
                if (get_user_input(&num1)) {
                    printf("Num2: ");
                    if (get_user_input(&num2)) {
                        printf("\n%ld - %ld = %ld\n", num1, num2, num1 - num2);
                        getchar();
                    }
                }
                break;
            case 3:
                printf("Num1: ");
                if (get_user_input(&num1)) {
                    printf("Num2: ");
                    if (get_user_input(&num2)) {
                        printf("\n%lu * %lu = %lu\n", num1, num2, num1 * num2);
                        getchar();
                    }
                }
                break;
            case 4:
                printf("Num1: ");
                if (get_user_input(&num1)) {
                    printf("Num2: ");
                    if (get_user_input(&num2)) {

                        printf("\n%ld / %ld = %0.2lf\n", num1, num2,
                               num1 / (float)num2);

                        getchar();
                    }
                }
                break;

            case 5:
                printf("Exiting calculator... \n");
                break;

            default:
                printf("Invalid input. Try again\n");
                getchar();
                break;
            }

        } else {
            printf("Invalid input. Try again\n");
            getchar();
        }
    }

    return 0;
}
