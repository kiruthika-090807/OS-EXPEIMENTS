/*
 * Experiment 27: Simulate the function of ls UNIX command
 * Lists all files in the current directory using opendir/readdir
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char path[256];

    printf("Enter directory path (or . for current): ");
    scanf("%255s", path);

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("\nDirectory listing of '%s':\n", path);
    printf("----------------------------------\n");

    while ((entry = readdir(dir)) != NULL) {
        /* Skip hidden files (like ls default behaviour) */
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
