/* 
====================================
* PROGRAM: 6.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a simple program to create three threads.
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void printThread(int num) {
    printf("Thread %d\n", num);
    sleep(40);
}

int main() {
    printf("PID: %d\n", getpid());

    pthread_t threads[3];
    int nums[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, (void*)printThread, &nums[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}