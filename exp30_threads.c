/*
 * Experiment 30: Demonstrate thread related concepts
 *   (i) create  (ii) join  (iii) equal  (iv) exit
 * Compile: gcc exp30_threads.c -o exp30_threads -lpthread
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func(void *arg) {
    pthread_detach(pthread_self());
    printf("Inside the thread\n");
    pthread_exit(NULL);
}

void fun() {
    pthread_t ptid;

    /* (i) create */
    pthread_create(&ptid, NULL, &func, NULL);
    printf("This line may be printed before thread terminates\n");

    /* (iii) equal */
    if (pthread_equal(ptid, pthread_self())) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    /* (ii) join */
    pthread_join(ptid, NULL);
    printf("This line will be printed after thread ends\n");

    /* (iv) exit */
    pthread_exit(NULL);
}

int main() {
    fun();
    return 0;
}
