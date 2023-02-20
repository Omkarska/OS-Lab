#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Global variables
int read_count = 0;      // Number of readers accessing or waiting for the resource
int shared_resource = 0; // The shared resource

// Mutex
pthread_mutex_t mutex; // Protects read_count

// Semaphore
sem_t wrt; // Signals when it is safe for writers to access shared_resource

// Reader function
void *reader(void *arg)
{
    int id = *((int *)arg); // Reader id

    while (1)
    {
        // Lock mutex before checking read_count
        pthread_mutex_lock(&mutex);

        // Increment read_count atomically
        read_count++;

        // If this is the first reader, wait until there are no writers accessing shared_resource by locking wrt
        if (read_count == 1)
        {
            sem_wait(&wrt);
        }

        // Unlock mutex after updating read count
        pthread_mutex_unlock(&mutex);

        // Read shared_resource
        printf("Reader %d reads %d\n", id, shared_resource);

        // Lock mutex before checking read count
        pthread_mutex_lock(&mutex);

        // Decrement read count atomically
        readcount--;

        // If this is the last reader unlock wrt so that writers can access sharedresource
        if (readcount == 0)
            sem_post(&wrt);

        // Unlock mutex after updating readcount
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

// Writer function
void *writer(void *arg)
{
    int id = *((int *)arg); // Writer id

    while (1)
    {
        // Wait until there are no readers or writers accessing sharedresource by locking wrt
        sem_wait(&wrt);

        // Write to sharedresource
        printf("Writer %d writes %d\n", id, ++sharedresource);

        // Unlock wrt after writing to sharedresource
        sem_post(&wrt);

        sleep(1);
    }

    return NULL;
}
