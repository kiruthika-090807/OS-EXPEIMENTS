/*
 * Experiment 36: Simulate Linked File Allocation Strategy
 * Each block is a node in a linked list; directory holds pointer
 * to the first and last block.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure to represent a disk block node */
struct Block {
    char          data[256];
    struct Block *next;
};

int main() {
    struct Block *firstBlock = NULL;
    struct Block *lastBlock  = NULL;
    int           blockCount = 0;
    char          choice;
    int           blockNumber;
    char          data[256];

    printf("Linked Allocation Simulation\n");
    printf("Commands: W = Write block, R = Read block, Q = Quit\n\n");

    while (1) {
        printf("Enter choice (W/R/Q): ");
        scanf(" %c", &choice);

        if (choice == 'Q' || choice == 'q') {
            break;
        } else if (choice == 'W' || choice == 'w') {
            printf("Enter data for the block: ");
            scanf(" %255[^\n]", data);

            struct Block *newBlock =
                (struct Block *)malloc(sizeof(struct Block));
            if (newBlock == NULL) {
                printf("Memory allocation failed.\n");
                break;
            }
            strncpy(newBlock->data, data, 255);
            newBlock->data[255] = '\0';
            newBlock->next      = NULL;

            if (blockCount == 0) {
                firstBlock = newBlock;
                lastBlock  = newBlock;
            } else {
                lastBlock->next = newBlock;
                lastBlock       = newBlock;
            }
            blockCount++;
            printf("Block %d written.\n", blockCount);

        } else if (choice == 'R' || choice == 'r') {
            if (blockCount == 0) {
                printf("No blocks written yet.\n");
                continue;
            }
            printf("Enter the block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);

            if (blockNumber < 1 || blockNumber > blockCount) {
                printf("Invalid block number. Valid range: 1-%d.\n", blockCount);
            } else {
                struct Block *current = firstBlock;
                for (int i = 1; i < blockNumber; i++)
                    current = current->next;
                printf("Block %d Data: %s\n", blockNumber, current->data);
            }
        } else {
            printf("Invalid choice. Use W, R, or Q.\n");
        }
    }

    /* Free allocated memory */
    struct Block *current = firstBlock;
    while (current != NULL) {
        struct Block *next = current->next;
        free(current);
        current = next;
    }

    printf("Exiting.\n");
    return 0;
}
