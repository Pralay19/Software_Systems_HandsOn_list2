/* 
====================================
* PROGRAM: 7.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a simple program to print the created thread ids.
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* printThreadID() {
    printf("Thread ID: %ld\n", pthread_self());
}

int main() {
printf("Process ID: %d\n", getpid());
pthread_t threads[3];

for (int i = 0; i < 3; i++) {
    pthread_create(&threads[i], NULL, printThreadID, NULL);
}

for (int i = 0; i < 3; i++) {
    pthread_join(threads[i], NULL);
}

return 0;
}