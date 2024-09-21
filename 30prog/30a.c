/* 
====================================
* PROGRAM: 30a.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

int main() {
    int token;
    int segm;
    char *buffer;

    token = ftok(".", 1);
    segm = shmget(token, 1024, IPC_CREAT | 0744);
    printf("Shared memory identifier: %d\n", segm);
    buffer = (char*)shmat(segm, NULL, 0);

    printf("Enter data to store: ");
    scanf("%s",buffer);

    printf("Data stored in shared memory.\n");
    return 0;
}