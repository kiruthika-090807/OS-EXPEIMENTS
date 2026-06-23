/*
 * Experiment 38: Simulate SCAN (Elevator) Disk Scheduling Algorithm
 * Head moves in one direction servicing requests until the end,
 * then reverses direction.
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

    printf("\nSCAN (Elevator) Disk Scheduling:\n");
    printf("Sorted requests: ");
    for (int i = 0; i < n; i++) printf("%d ", rq[i]);
    printf("\n");

    /*
     * Strategy:
     * 1. Service all requests >= head (moving right/up).
     * 2. Service remaining requests < head in reverse (moving left/down).
     */
    printf("Head Movement: %d", head);

    /* Move right: service requests >= head in ascending order */
    for (int i = 0; i < n; i++) {
        if (rq[i] >= head) {
            seek_time += abs(head - rq[i]);
            head = rq[i];
            printf(" -> %d", head);
        }
    }

    /* Move left: service requests < original head in descending order */
    for (int i = n - 1; i >= 0; i--) {
        if (rq[i] < head) {      /* rq[i] is already < original head */
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
