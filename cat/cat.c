#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int read_file(const char* filename);

int main(int argc, char* argv[]) {
    // if (argc != 2) { 
    //     printf("Usage: %s filename\n", argv[0]); 
    //     return 1; 
    // }
    printf("%d", argc);
    read_file(argv[1]); 

    system("pause");
    return 0;
}

int read_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    char ch;

    if (file == NULL) {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    while ((ch = fgetc(file)) != EOF)
        putchar(ch);

    fclose(file);

    return 0;
}