#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

float checkSize(char file_name[]);

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *dent;
    const char *name = ".";

    if(argc > 1)
        name = argv[1];

    dir = opendir(name);

    if(!dir)
    {
        perror(name);
        return 1;
    }

    printf("File Name     File Exstention     File Size\n");
    while((dent = readdir(dir)) != NULL) {
        const char *file_extension = strrchr(dent->d_name, '.');
        if (file_extension == NULL) {
            file_extension = "DIR";
        }
        printf("%-19s %-16s %-16.2f KB\n", dent->d_name, file_extension, checkSize(dent->d_name));
    }

    closedir(dir);
    return 0;
}

float checkSize(char file_name[]) {
    FILE* file = fopen(file_name, "r");
    float bytes;
    float kilo_bytes;

    fseek(file, 0L, SEEK_END);
    bytes = ftell(file);
    fclose(file);

    kilo_bytes = bytes / 1024;
    
    return kilo_bytes;
}
