/*
 * Experiment 31: Simulate First In First Out (FIFO) paging technique
 */

#include <stdio.h>

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
    int framePointer = 0; /* Points to the oldest frame (FIFO) */
    int pageFaults   = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1; /* -1 means empty */

    printf("Reference String: ");
    for (int i = 0; i < n; i++)
        printf("%d ", referenceString[i]);
    printf("\n\n");

    printf("Page Replacement Order:\n");

    for (int i = 0; i < n; i++) {
        int page      = referenceString[i];
        int pageFound = 0;

        /* Check if page already in frames (hit) */
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            /* Page fault */
            pageFaults++;
            printf("Page %d -> FAULT | Frames: ", page);
            frames[framePointer] = page;
            framePointer = (framePointer + 1) % MAX_FRAMES;
            printFrames(frames, MAX_FRAMES);
        } else {
            printf("Page %d -> HIT   | Frames: ", page);
            printFrames(frames, MAX_FRAMES);
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
