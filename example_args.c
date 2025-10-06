#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("Number of arguments: %d\n", argc);
    printf("Program name: %s\n", argv[0]);
    
    if (argc > 1) {
        printf("Arguments passed:\n");
        for (int i = 1; i < argc; i++) {
            printf("  argv[%d] = %s\n", i, argv[i]);
        }
    } else {
        printf("No arguments passed.\n");
    }
    
    return 0;
}