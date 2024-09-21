/* 
====================================
* PROGRAM: 32b.c
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
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define SHARED_KEY 1234
#define SHARED_SIZE 100

int sharedMemoryId;
char *sharedMemoryPtr;
sem_t semaphore;

void* writeToSharedMemory(void* arg) {

    char* msg = (char*)arg;
    sem_wait(&semaphore);
    strcpy(sharedMemoryPtr, msg);
    sem_post(&semaphore);
    pthread_exit(NULL);
}

int main() {

    sharedMemoryId = shmget(SHARED_KEY, SHARED_SIZE, IPC_CREAT | 0666);
    if (sharedMemoryId == -1) {
        perror("shmget_error");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory ID: %d\n", sharedMemoryId);

    sharedMemoryPtr = shmat(sharedMemoryId, NULL, 0);
    if (sharedMemoryPtr == (char *)-1) {
        perror("shmat_error");
        exit(EXIT_FAILURE);
    }

    sem_init(&semaphore, 0, 1);

    pthread_t writer1, writer2;
    char* messageFromThread1 = "Data from Writer 1";
    char* messageFromThread2 = "Data from Writer 2";

    pthread_create(&writer1, NULL, writeToSharedMemory, (void*)messageFromThread1);
    printf("Current shared memory content: %s\n", sharedMemoryPtr);

    pthread_create(&writer2, NULL, writeToSharedMemory, (void*)messageFromThread2);
    printf("Current shared memory content: %s\n", sharedMemoryPtr);

    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);

    printf("Final shared memory content: %s\n", sharedMemoryPtr);

    shmdt(sharedMemoryPtr);

    return 0;
}
