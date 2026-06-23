/*
 * Experiment 34: Simulate Sequential (Contiguous) File Allocation Strategy
 * Records are stored one after another; a record can only be accessed
 * by reading all previous records.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure to represent a record */
struct Record {
    int  recordNumber;
    char data[256];
};

int main() {
    FILE        *file;
    struct Record record;
    int          recordNumber;

    /* ---- WRITE phase ---- */
    file = fopen("sequential_file.txt", "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter records (Enter 0 as record number to stop):\n");
    while (1) {
        printf("Record Number: ");
        if (scanf("%d", &record.recordNumber) != 1) break;
        if (record.recordNumber == 0) break;

        printf("Data: ");
        scanf(" %255[^\n]", record.data);

        fwrite(&record, sizeof(struct Record), 1, file);
    }
    fclose(file);

    /* ---- READ phase ---- */
    file = fopen("sequential_file.txt", "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (1) {
        printf("\nEnter the record number to read (0 to exit): ");
        if (scanf("%d", &recordNumber) != 1) break;
        if (recordNumber == 0) break;

        rewind(file);
        int found = 0;
        while (fread(&record, sizeof(struct Record), 1, file) == 1) {
            if (record.recordNumber == recordNumber) {
                printf("Record Number: %d\n", record.recordNumber);
                printf("Data: %s\n", record.data);
                found = 1;
                break;
            }
        }
        if (!found)
            printf("Record %d not found.\n", recordNumber);
    }

    fclose(file);
    return 0;
}
