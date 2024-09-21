/* 
====================================
* PROGRAM: 32c.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
====================================
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sharedData[2];
sem_t syncLock;

void* accessResource(void* arg) {
    int id = *(int*)arg;

    sem_wait(&syncLock);

    printf("Accessing resource %d.\n", id);
    sharedData[id] = 0;

    sem_post(&syncLock);

    pthread_exit(NULL);
}

int main() {
    pthread_t threadPool[2];
    int threadIds[2];

    sem_init(&syncLock, 0, 2);

    for (int i = 0; i < 2; ++i) {
        sharedData[i] = 1;
        threadIds[i] = i;
        pthread_create(&threadPool[i], NULL, accessResource, (void*)&threadIds[i]);
    }

    for (int i = 0; i < 2; ++i) {
        pthread_join(threadPool[i], NULL);
    }

    sem_destroy(&syncLock);
    return 0;
}
