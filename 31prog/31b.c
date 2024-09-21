/* 
====================================
* PROGRAM: 31b.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};

int main() {
    int sem_key = ftok(".", 1);
    if (sem_key == -1) {
        perror("ftok_error");
        exit(EXIT_FAILURE);
    }

    int sem_id = semget(sem_key, 1, IPC_CREAT | 0777);
    if (sem_id == -1) {
        perror("semget_error");
        exit(EXIT_FAILURE);
    }

    union semun sem_arg;
    sem_arg.val = 100;  // Initialize as a counting semaphore

    int sem_status = semctl(sem_id, 0, SETVAL, sem_arg);
    if (sem_status != -1) {
        printf("Counting semaphore created and initialized successfully\n");
    } else {
        perror("semctl_error");
        exit(EXIT_FAILURE);
    }

    return 0;
}
