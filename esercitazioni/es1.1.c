#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int first;
    float second;

    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc - 1);

    if (argc == 1)
        printf("No arguments\n");
    else
        if (argc == 2) {
            printf("first arguments: %s\n", argv[1]);
            first = atoi(argv[1]);
            printf("first arguments: %d\n", first);
        }
        else
            if (argc == 3) {
                printf("arguments %s %s\n", argv[1], argv[2]);
                first = atoi(argv[1]);
                second = atof(argv[2]);
                printf("arguments %d %f\n", first, second);
            }
            else {
                fprintf(stderr, "Wrong number of arguments!\n");
                return EXIT_FAILURE;
            }
    return EXIT_SUCCESS;
}
