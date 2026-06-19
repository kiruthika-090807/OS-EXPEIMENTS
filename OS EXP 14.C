#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void copyFile()
{
    const char *sourcefile =
        "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    const char *destination_file =
        "C:/Users/itssk/OneDrive/Desktop/sk.txt";

    int source_fd = open(sourcefile, O_RDONLY);

    if (source_fd < 0)
    {
        printf("Cannot open source file\n");
        return;
    }

    int dest_fd = open(destination_file,
                       O_WRONLY | O_CREAT | O_TRUNC,
                       0666);

    if (dest_fd < 0)
    {
        printf("Cannot create destination file\n");
        close(source_fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        write(dest_fd, buffer, bytesRead);
    }

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
}

void createFile()
{
    FILE *fp;

    fp = fopen(
        "C:/Users/itssk/OneDrive/Desktop/sasi.txt",
        "w");

    if (fp == NULL)
    {
        printf("File creation failed.\n");
        return;
    }

    fclose(fp);

    printf("File created successfully.\n");
}

void deleteFile()
{
    if (remove(
            "C:/Users/itssk/OneDrive/Desktop/sasi.txt") == 0)
    {
        printf("File deleted successfully.\n");
    }
    else
    {
        printf("Unable to delete file.\n");
    }
}

int main()
{
    int n;

    printf("1. Create\n");
    printf("2. Copy\n");
    printf("3. Delete\n");
    printf("Enter your choice: ");
    scanf("%d", &n);

    switch (n)
    {
    case 1:
        createFile();
        break;

    case 2:
        copyFile();
        break;

    case 3:
        deleteFile();
        break;

    default:
        printf("Invalid Choice\n");
    }

    return 0;
}
