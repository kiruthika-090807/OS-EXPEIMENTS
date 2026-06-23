/*
 * Experiment 35: Simulate Indexed File Allocation Strategy
 * An index block holds pointers (offsets) to each data block.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100

/* Structure to represent a data block */
struct Block {
    int  blockNumber;
    char data[256];
};

int main() {
    FILE        *file;
    struct Block block;
    int          blockNumber;
    long         indexBlock[MAX_BLOCKS];  /* index: blockNumber -> file offset */

    /* Initialise index block to -1 (not present) */
    for (int i = 0; i < MAX_BLOCKS; i++)
        indexBlock[i] = -1;

    /* ---- WRITE phase ---- */
    file = fopen("indexed_file.bin", "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter blocks (Enter 0 as block number to stop):\n");
    while (1) {
        printf("Block Number (1-%d): ", MAX_BLOCKS - 1);
        if (scanf("%d", &block.blockNumber) != 1) break;
        if (block.blockNumber == 0) break;
        if (block.blockNumber < 1 || block.blockNumber >= MAX_BLOCKS) {
            printf("Invalid block number.\n");
            continue;
        }

        printf("Data: ");
        scanf(" %255[^\n]", block.data);

        /* Record offset before writing */
        long offset = ftell(file);
        fwrite(&block, sizeof(struct Block), 1, file);
        indexBlock[block.blockNumber] = offset;
    }
    fclose(file);

    /* ---- READ phase ---- */
    file = fopen("indexed_file.bin", "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (1) {
        printf("\nEnter the block number to read (0 to exit): ");
        if (scanf("%d", &blockNumber) != 1) break;
        if (blockNumber == 0) break;

        if (blockNumber < 1 || blockNumber >= MAX_BLOCKS ||
            indexBlock[blockNumber] == -1) {
            printf("Block %d not found in index.\n", blockNumber);
        } else {
            fseek(file, indexBlock[blockNumber], SEEK_SET);
            fread(&block, sizeof(struct Block), 1, file);
            printf("Block Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file);
    return 0;
}
