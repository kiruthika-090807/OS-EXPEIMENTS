#include <stdio.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5

int main()
{
    int i;

    printf("Dining Philosophers Problem Simulation\n\n");

    for(i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        printf("Philosopher %d is thinking...\n", i);
        printf("Philosopher %d picks up left chopstick.\n", i);
        printf("Philosopher %d picks up right chopstick.\n", i);
        printf("Philosopher %d is eating...\n", i);
        printf("Philosopher %d puts down left chopstick.\n", i);
        printf("Philosopher %d puts down right chopstick.\n\n", i);
    }

    return 0;
}
