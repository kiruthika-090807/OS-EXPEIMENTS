#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE] = {0};

sem_t empty, full;

int produced_items = 0;
int consumed_items = 0;

void *producer(void *arg)
{
    while (produced_items < MAX_ITEMS)
    {
        sem_wait(&empty);

        /* Critical Section: Produce Item */
        int i;
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (buffer[i] == 0)
            {
                buffer[i] = produced_items + 1;
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }

        sem_post(&full);
        Sleep(1000);
    }

    return NULL;
}

void *consumer(void *arg)
{
    while (consumed_items < MAX_ITEMS)
    {
        sem_wait(&full);

        /* Critical Section: Consume Item */
        int i;
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (buffer[i] != 0)
            {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;
                consumed_items++;
                break;
            }
        }

        sem_post(&empty);
        Sleep(2000);
    }

    return NULL;
}

int main()
{
    pthread_t producer_thread;
    pthread_t consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
