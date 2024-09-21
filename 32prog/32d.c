/* 
====================================
* PROGRAM: 32d.c
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
#include <sys/sem.h>

union semun {
    int value;
    struct semid_ds *buffer;
    unsigned short int *array;
};

int main() {

    key_t semaphoreKey = ftok(".", 1);
    if (semaphoreKey == -1) {
        perror("Error generating key with ftok");
        exit(EXIT_FAILURE);
    }

    int semaphoreId = semget(semaphoreKey, 1, IPC_CREAT | 0777);
    if (semaphoreId == -1) {
        perror("Error creating semaphore");
        exit(EXIT_FAILURE);
    }

    union semun semaphoreConfig;
    semaphoreConfig.value = 1;  // Initialize as binary semaphore

    if (semctl(semaphoreId, 0, SETVAL, semaphoreConfig) != -1) {
        printf("Binary semaphore created and initialized with ID %d\n", semaphoreId);
    } else {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }

    system("ipcs -s");  // Display semaphore status before removal

    if (semctl(semaphoreId, 0, IPC_RMID) == -1) {
        perror("Error removing semaphore");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore removed successfully\n");

    system("ipcs -s");  // Display semaphore status after removal

    return 0;
}
