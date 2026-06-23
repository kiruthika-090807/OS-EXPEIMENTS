/*
 * Experiment 28: Simulation of GREP UNIX command
 * Usage: ./exp28_grep_simulation <pattern> <filename>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void searchFile(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int lineNum = 0;
    while (fgets(line, sizeof(line), file)) {
        lineNum++;
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", lineNum, line);
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }
    const char *pattern  = argv[1];
    const char *filename = argv[2];
    searchFile(pattern, filename);
    return 0;
}
