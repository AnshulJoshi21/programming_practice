#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Invalid input\n");
        return 1;
    }

    char buffer[1024];

    const char* grep_text = argv[1];
    const char* file_name = argv[2];

    FILE* file = fopen(file_name, "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, grep_text) != NULL) {
            printf("%s", buffer);
        }
    }

    fclose(file);

    return 0;
}
