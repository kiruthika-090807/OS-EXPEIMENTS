/*
 * Experiment 40: Illustrate File Access Permissions and types of users in Linux
 * Demonstrates: chmod(), stat(), and permission bit interpretation
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* Print human-readable permission string like ls -l */
void printPermissions(mode_t mode) {
    printf("Permissions: ");
    printf("%c", S_ISREG(mode) ? '-' : (S_ISDIR(mode) ? 'd' : 'l'));

    /* Owner */
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');

    /* Group */
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');

    /* Others */
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
    printf("\n");
}

int main() {
    const char *filename = "file.txt";

    /* Create the file if it does not exist */
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "Sample file for permission demo.\n");
    fclose(fp);

    /* Show initial permissions */
    struct stat st;
    if (stat(filename, &st) != 0) { perror("stat"); return 1; }
    printf("--- Initial Permissions ---\n");
    printPermissions(st.st_mode);

    /* Change permissions: rw-rw-r-- (Owner: rw, Group: rw, Others: r) */
    int new_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

    if (chmod(filename, new_permissions) == 0) {
        printf("\nPermissions changed to rw-rw-r-- successfully.\n");
    } else {
        perror("chmod");
        return 1;
    }

    /* Show updated permissions */
    if (stat(filename, &st) != 0) { perror("stat"); return 1; }
    printf("\n--- Updated Permissions ---\n");
    printPermissions(st.st_mode);

    printf("\nPermission breakdown:\n");
    printf("  Owner  : Read=%s, Write=%s, Execute=%s\n",
           (st.st_mode & S_IRUSR) ? "Yes" : "No",
           (st.st_mode & S_IWUSR) ? "Yes" : "No",
           (st.st_mode & S_IXUSR) ? "Yes" : "No");
    printf("  Group  : Read=%s, Write=%s, Execute=%s\n",
           (st.st_mode & S_IRGRP) ? "Yes" : "No",
           (st.st_mode & S_IWGRP) ? "Yes" : "No",
           (st.st_mode & S_IXGRP) ? "Yes" : "No");
    printf("  Others : Read=%s, Write=%s, Execute=%s\n",
           (st.st_mode & S_IROTH) ? "Yes" : "No",
           (st.st_mode & S_IWOTH) ? "Yes" : "No",
           (st.st_mode & S_IXOTH) ? "Yes" : "No");

    return 0;
}
