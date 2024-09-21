/* 
====================================
* PROGRAM: 32a.c
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
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int ticketCount = 0;
sem_t lock;

void* ticketSeller(void* arg) {
    while (1) {
        sem_wait(&lock);
        if (ticketCount < 50) {
            ticketCount++;
            printf("Ticket %d sold by thread %ld\n", ticketCount, pthread_self());
        } else {
            sem_post(&lock);
            break;
        }
        sem_post(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t seller1, seller2;

    sem_init(&lock, 0, 1);

    pthread_create(&seller1, NULL, ticketSeller, NULL);
    pthread_create(&seller2, NULL, ticketSeller, NULL);

    pthread_join(seller1, NULL);
    pthread_join(seller2, NULL);

    sem_destroy(&lock);

    return 0;
}
