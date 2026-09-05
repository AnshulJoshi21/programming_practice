#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define BUFFER_SIZE 100
#define TASK_SIZE 1024

typedef struct {
    char text[TASK_SIZE];
} Task;

int main(void) {
    char buffer[BUFFER_SIZE];
    bool running = true;

    Task tasks[MAX_TASKS];
    int  task_size = 0;

    while (running) {
        system("clear");

        printf("Todo Manager\n\n");
        printf("1) Add\n");
        printf("2) Delete\n");
        printf("3) View\n");
        printf("4) Save\n");
        printf("5) Exit\n");

        printf("> ");
        assert(fgets(buffer, sizeof(buffer), stdin));
        buffer[strcspn(buffer, "\n")] = '\0';

        int input = atoi(buffer);

        switch (input) {
            // ADD
            case 1: {
                if (task_size >= MAX_TASKS) {
                    printf("Task list full\n");
                    printf("press 'enter' to continue...\n");
                    getchar();
                    continue;
                }

                Task task;

                assert(fgets(task.text, sizeof(task.text), stdin));
                task.text[strcspn(task.text, "\n")] = '\0';
                tasks[task_size++]                  = task;

                printf("Task Added!\n");
                printf("press 'enter' to continue...\n");
                getchar();
            } break;

            // DELETE
            case 2: {
                if (task_size == 0) {
                    printf("No task to delete\n");
                    printf("press 'enter' to continue...\n");
                    getchar();
                    continue;
                }

                printf("Task Index: ");
                assert(fgets(buffer, sizeof(buffer), stdin));
                buffer[strcspn(buffer, "\n")] = '\0';

                // tasks start from 1 in view
                int index = atoi(buffer) - 1;

                if (index < 0 || index >= task_size) {
                    printf("Invalid index\n");
                    printf("press 'enter' to continue...\n");
                    getchar();
                    continue;
                }

                for (int i = index; i < task_size - 1; i++) {
                    tasks[i] = tasks[i + 1];
                }
                task_size--;
                if (task_size < 0) task_size = 0;

                printf("Task Deleted!\n");
                printf("press 'enter' to continue...\n");
                getchar();
            } break;

            // VIEW
            case 3: {
                if (task_size == 0) {
                    printf("No Tasks Found\n");
                    printf("press 'enter' to continue...\n");
                    getchar();
                    continue;
                }

                for (int i = 0; i < task_size; i++) {
                    printf("%d. %s\n", i + 1, tasks[i].text);
                }
                printf("\npress 'enter' to continue...\n");
                getchar();
            } break;

            // SAVE
            case 4: {
                FILE* fp = NULL;
                fp       = fopen("tasks.txt", "w");
                assert(fp);
                for (int i = 0; i < task_size; i++) {
                    fprintf(fp, "%s\n", tasks[i].text);
                }
                fclose(fp);

                printf("Tasks Saved\n");
                printf("press 'enter' to continue...\n");
                getchar();
            } break;

                // EXIT
            case 5: {
                printf("Exiting program...\n");
                running = false;
            } break;

            // ERROR
            default: {
                printf("invalid input\n");
                printf("press 'enter' to continue...\n");
                getchar();
            } break;
        }
    }
    return 0;
}
