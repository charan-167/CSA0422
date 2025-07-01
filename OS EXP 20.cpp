#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 10; i++) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock); // First reader blocks writers
        }
        sem_post(&mutex);

        // Reading operation
        printf("Reader %d reads data: %d\n", id, data);

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock); // Last reader unblocks writers
        }
        sem_post(&mutex);

        usleep(100000); // Sleep 100ms
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 10; i++) {
        sem_wait(&writeBlock); // Writer blocks readers and other writers

        // Writing operation
        data++;
        printf("Writer %d writes data: %d\n", id, data);

        sem_post(&writeBlock);
        usleep(150000); // Sleep 150ms
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int r_ids[NUM_READERS], w_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        r_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &r_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        w_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &w_ids[i]);
    }

    // Join all threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}
