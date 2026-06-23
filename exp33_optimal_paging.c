/*
 * Experiment 33: Simulate Optimal paging technique
 * Replaces the page that will NOT be used for the longest time in future.
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
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    int frames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    printf("Reference String: ");
    for (int i = 0; i < n; i++)
        printf("%d ", referenceString[i]);
    printf("\n\n");

    printf("Page Replacement Order:\n");

    for (int i = 0; i < n; i++) {
        int page      = referenceString[i];
        int pageFound = 0;

        /* Check for hit */
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            pageFaults++;

            /* Check for empty slot first */
            int emptySlot = -1;
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }

            if (emptySlot != -1) {
                frames[emptySlot] = page;
                printf("Page %d -> FAULT | Loaded into empty frame | Frames: ", page);
            } else {
                /* Find optimal page to replace */
                int optimalSlot      = 0;
                int farthestDistance = -1;

                for (int j = 0; j < MAX_FRAMES; j++) {
                    int futureDistance = n; /* default: never used again */
                    for (int k = i + 1; k < n; k++) {
                        if (referenceString[k] == frames[j]) {
                            futureDistance = k - i;
                            break;
                        }
                    }
                    if (futureDistance > farthestDistance) {
                        farthestDistance = futureDistance;
                        optimalSlot      = j;
                    }
                }

                int replacedPage      = frames[optimalSlot];
                frames[optimalSlot]   = page;
                printf("Page %d -> FAULT | Replaced %d | Frames: ", page, replacedPage);
            }

            printFrames(frames, MAX_FRAMES);
        } else {
            printf("Page %d -> HIT   | Frames: ", page);
            printFrames(frames, MAX_FRAMES);
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
