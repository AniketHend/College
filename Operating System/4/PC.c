#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct queue
{
    int arr[1000];
    sem_t empty, full;
    int in, out;
    pthread_mutex_t lock;
} queue;
#define size 10
queue buffer;

void *producer(void *ind)
{
    int index = *(int *)(ind);
    while (1)
    {
        sem_wait(&buffer.empty);
        int v;
        sem_getvalue(&buffer.empty, &v);
        if (v == 0)
        {
            printf("buffer is full\n");
        }
        pthread_mutex_lock(&buffer.lock);
        buffer.arr[(buffer.out++) % size] = (rand()) % 10 + 1;
        printf("producer %d  is producing an item %d\n", index, buffer.arr[(buffer.out - 1 + size) % size]);
        pthread_mutex_unlock(&buffer.lock);
        sem_post(&buffer.full);
    }
}

void *consumer(void *ind)
{
    int index = *(int *)(ind);
    while (1)
    {
        sem_wait(&buffer.full);
        int v;
        sem_getvalue(&buffer.full, &v);
        if (v == size)
        {
            printf("buffer is empty\n");
        }
        pthread_mutex_lock(&buffer.lock);
        printf("consumer %d  is consuming an item %d \n", index, buffer.arr[(buffer.in++) % size]);
        pthread_mutex_unlock(&buffer.lock);
        sem_post(&buffer.empty);
    }
}
int main()
{
    pthread_t prod[size];
    pthread_t cons[size];

    int p, c;
    printf("enter no of producers :: ");
    scanf("%d", &p);
    printf("enter no of consumers :: ");
    scanf("%d", &c);

    buffer.in = 0;
    buffer.out = 0;
    sem_init(&buffer.full, 0, 0);
    sem_init(&buffer.empty, 0, size);

    for (int i = 0; i < p; i++)
    {
        pthread_create(&prod[i], NULL, *producer, &i);
    }
    for (int i = 0; i < c; i++)
    {
        pthread_create(&cons[i], NULL, *consumer, &i);
    }

    for (int i = 0; i < p; i++)
    {
        pthread_join(prod[i], NULL);
    }
    for (int i = 0; i < c; i++)
    {
        pthread_join(cons[i], NULL);
    }

    // sem_destroy(&buffer.em);
    // sem_destroy(&buffer.fu);
    // pthread_mutex_destroy(&buffer.lck);
}
