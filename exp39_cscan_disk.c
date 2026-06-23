/*
 * Experiment 39: Simulate C-SCAN (Circular SCAN) Disk Scheduling Algorithm
 * Head moves in one direction servicing requests; when it reaches the end
 * it jumps back to the beginning and continues in the same direction.
 */

#include <stdio.h>
#include <stdlib.h>

/* Simple bubble sort helper */
void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j]) {
                int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }
}

int main() {
    int n, head;
    int seek_time = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    int *rq = (int *)malloc(n * sizeof(int));
    if (rq == NULL) { printf("Memory allocation failed.\n"); return 1; }

    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        printf("  Request %d: ", i + 1);
        scanf("%d", &rq[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    sortArray(rq, n);

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Sorted requests: ");
    for (int i = 0; i < n; i++) printf("%d ", rq[i]);
    printf("\n");

    /*
     * Strategy:
     * 1. Service all requests >= head in ascending order.
     * 2. Jump to cylinder 0 (seek cost added).
     * 3. Service remaining requests < original head in ascending order.
     */
    int initialHead = head;
    printf("Head Movement: %d", head);

    /* Phase 1: move right, service requests >= head */
    for (int i = 0; i < n; i++) {
        if (rq[i] >= head) {
            seek_time += abs(head - rq[i]);
            head = rq[i];
            printf(" -> %d", head);
        }
    }

    /* Phase 2: jump to cylinder 0 */
    if (head != 0) {
        seek_time += head; /* cost of moving from current pos to 0 */
        head = 0;
        printf(" -> 0 (jump)");
    }

    /* Phase 3: service requests < initialHead in ascending order */
    for (int i = 0; i < n; i++) {
        if (rq[i] < initialHead) {
            seek_time += abs(head - rq[i]);
            head = rq[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time  : %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    free(rq);
    return 0;
}
