#include <stdio.h>
#include <pthread.h>

/* Shared Variable */
int counter = 0;

/* Mutex Variable */
pthread_mutex_t mutex;

/* Function executed by threads */
void *threadFunction(void *arg)
{
    int i;

    for (i = 0; i < 1000000; ++i)
    {
        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    /* Initialize Mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Create Threads */
    pthread_create(&thread1, NULL, threadFunction, NULL);
    pthread_create(&thread2, NULL, threadFunction, NULL);

    /* Wait for Threads to Finish */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    /* Destroy Mutex */
    pthread_mutex_destroy(&mutex);

    /* Display Final Counter Value */
    printf("Final counter value: %d\n", counter);

    return 0;
}
