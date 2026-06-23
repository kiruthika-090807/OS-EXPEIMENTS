/*
 * Experiment 32: Simulate Least Recently Used (LRU) paging technique
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

int main() {
    int frames[MAX_FRAMES];
    int usageHistory[MAX_FRAMES]; /* higher value = used less recently */
    int pageFaults = 0;

    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i]       = -1;
        usageHistory[i] = 0;
    }

    printf("Reference String: ");
    for (int i = 0; i < n; i++)
        printf("%d ", referenceString[i]);
    printf("\n\n");

    printf("Page Replacement Order:\n");

    for (int i = 0; i < n; i++) {
        int page      = referenceString[i];
        int pageFound = 0;

        /* Check for page hit */
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                /* Age all other pages, reset this one */
                for (int k = 0; k < MAX_FRAMES; k++) {
                    if (k != j)
                        usageHistory[k]++;
                }
                usageHistory[j] = 0;
                break;
            }
        }

        if (!pageFound) {
            /* Page fault: find LRU slot (highest usageHistory) */
            int lruSlot = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (usageHistory[j] > usageHistory[lruSlot])
                    lruSlot = j;
            }

            int replacedPage = frames[lruSlot];
            frames[lruSlot]       = page;
            usageHistory[lruSlot] = 0;

            /* Age remaining pages */
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (j != lruSlot)
                    usageHistory[j]++;
            }

            pageFaults++;
            printf("Page %d -> FAULT | ", page);
            if (replacedPage != -1)
                printf("Replaced %d | Frames: ", replacedPage);
            else
                printf("Loaded into empty frame | Frames: ");

            printFrames(frames, MAX_FRAMES);
        } else {
            printf("Page %d -> HIT   | Frames: ", page);
            printFrames(frames, MAX_FRAMES);
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
