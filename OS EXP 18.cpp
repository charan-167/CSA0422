#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h> // For Sleep() on Windows

#define BUFFER_SIZE 5
#define MAX_ITEMS 10 // Maximum number of items to be produced/consumed

int buffer[BUFFER_SIZE] = {0};
sem_t empty, full;

int produced_items = 0;
int consumed_items = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (produced_items >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&empty);

        pthread_mutex_lock(&mutex);
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] == 0) {
                buffer[i] = produced_items + 1;
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        sem_post(&full);
        Sleep(100); // Sleep for 100ms
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (consumed_items >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&full);

        pthread_mutex_lock(&mutex);
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] != 0) {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;
                consumed_items++;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
        Sleep(200); // Sleep for 200ms
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_mutex_destroy(&mutex);

    return 0;
}
