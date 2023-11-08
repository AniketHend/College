#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_resource = 0;                                        // Shared resource
int readers_count = 0;                                          // Number of active readers
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;              // mutex for mutual exclusion
pthread_mutex_t reader_count_mutex = PTHREAD_MUTEX_INITIALIZER; // mutex to protect readers_count

void *reader(void *reader_id)
{
    int id = *((int *)reader_id);

    while (1)
    {
        // Entry section
        pthread_mutex_lock(&reader_count_mutex);
        readers_count++;
        if (readers_count == 1)
        { // First reader, lock the shared resource
            pthread_mutex_lock(&mutex);
        }
        pthread_mutex_unlock(&reader_count_mutex);

        // Reading the shared resource
        printf("Reader %d is reading: %d\n", id, shared_resource);

        // Exit section
        pthread_mutex_lock(&reader_count_mutex);
        readers_count--;
        if (readers_count == 0)
        { // Last reader, release the shared resource
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_unlock(&reader_count_mutex);

        // Simulate some reading time
        sleep(2);
    }
}

void *writer(void *writer_id)
{
    int id = *((int *)writer_id);

    while (1)
    {
        // Writing the shared resource
        pthread_mutex_lock(&mutex);
        printf("Writer %d is writing: %d\n", id, ++shared_resource);
        pthread_mutex_unlock(&mutex);
        // Simulate some writing time
        sleep(2);
    }
}

int main()
{
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }


    // Wait for threads to finish
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    return 0;
}
