#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

float checkSize(char file_name[]);

int main() {
    DIR *d = opendir(".");
    struct dirent *dir;

    if(d == NULL) {
        perror("opendir");
        return 1;
    }

    printf("File Name     File Exstention     File Size\n");
    while((dir = readdir(d)) != NULL) {
        printf("%-19s %-16s %-16.2f KB\n", dir->d_name, strrchr(dir->d_name, '.'), checkSize(dir->d_name));
    }

    closedir(d);
    system("pause");
    return 0;
}

float checkSize(char file_name[]) {
    FILE* file = fopen(file_name, "r");
    float bytes;
    float kilo_bytes;

    fseek(file, 0L, SEEK_END);
    bytes = ftell(file);
    fclose(file);

    kiloBytes = bytes / 1024;
    
    return kilo_bytes;
}
