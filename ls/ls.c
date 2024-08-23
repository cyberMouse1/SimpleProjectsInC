#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static char *get_file_extension(const char *filename);
static float get_size_file(char filename[]);
static int is_directory(const char *path);
static void print_ls(int argument_count, char *argument_value[]);

int main(int argc, char *argv[])
{
    print_ls(argc, argv);

    return 0;
}

static char *get_file_extension(const char *filename)
{
    char *last_dot = strrchr(filename, '.');
    if (last_dot != NULL) {
        return last_dot + 1;
    } else {
        return "Not found";
    }
}

static float get_size_file(char filename[])
{
    FILE* file = fopen(filename, "r");
    float bytes;

    if(file == NULL) {
        return 0.00;
    }

    fseek(file, 0L, SEEK_END);
    bytes = ftell(file);
    fclose(file);
    
    return bytes / 1024;
}

static int is_directory(const char *path)
{
    struct stat stats;
    stat(path, &stats);

    if(S_ISDIR(stats.st_mode))
        return 0;
    
    return 1;
}

static void print_ls(int argument_count, char *argument_value[])
{
    DIR *dir;
    struct dirent *dent;
    const char *name = ".";

    dir = opendir(name);

    if(!dir)
        perror(name);

    if(argument_count > 1)
        name = argument_value[1];

    printf("File Name     File Exstention     File Size\n");
    while((dent = readdir(dir)) != NULL) {
        if(is_directory(dent->d_name) == 0)
            printf("%-18s %-15s\n", dent->d_name, "DIR");
        else
            printf("%-18s %-15s %.2f KB\n", dent->d_name, get_file_extension(dent->d_name), get_size_file(dent->d_name));
    }

    closedir(dir);
}
