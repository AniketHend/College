// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>

// #define size 10

// typedef struct queue
// {
//     int arr[100000];
//     int in, out;
//     sem_t fu, em;
//     pthread_mutex_t lck;
// } queue;

// queue buffer;
// int itm;
// int produced = 0;
// void print_buffer()
// {
//     printf("Buffer %d:: [", produced);
//     for (int i = buffer.out; i < buffer.out + produced; i++)
//     {
//         printf("%d ,", buffer.arr[i]);
//     }
//     printf("]\n");
// }
// void *pro(void *arg)
// {
//     int index = *(int *)(arg);
//     int z;

//     while (1)
//     {
//         z = (rand() % 10) + 1;
//         sleep(z);
//         sem_wait(&buffer.em);
//         int v;
//         sem_getvalue(&buffer.em, &v);
//         if (v == 0)
//         {
//             printf("buffer full");
//         }
//         pthread_mutex_lock(&buffer.lck);
//         itm = (rand() % 10) + 1;
//         printf("\nProducer %d is producing item %d\n", index, itm);
//         buffer.arr[(buffer.in++) % size] = itm;
//         produced++;
//         pthread_mutex_unlock(&buffer.lck);
//         sem_post(&buffer.fu);
//         print_buffer();
//     }
// }

// void *con(void *arg)
// {
//     int index = *(int *)(arg);
//     int z;

//     while (1)
//     {
//         z = (rand() % 10) + 1;
//         sleep(z);
//         sem_wait(&buffer.fu);
//         int v;
//         sem_getvalue(&buffer.fu, &v);
//         if (v == size)
//         {
//             printf("buffer empty");
//         }
//         pthread_mutex_lock(&buffer.lck);
//         itm = buffer.arr[(buffer.out++) % size];
//         printf("\nConsumer %d is consuming item %d\n", index, itm);
//         produced--;
//         pthread_mutex_unlock(&buffer.lck);
//         sem_post(&buffer.em);
//         print_buffer();
//     }
// }
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