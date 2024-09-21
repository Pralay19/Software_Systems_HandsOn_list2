/* 
====================================
* PROGRAM: 30b.c
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
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>

int main() {
    int token;
    int shmid;
    char *buffer;

    token = ftok(".", 1);
    shmid = shmget(token, 1024, 0);

    if (shmid == -1) {
        perror("shmget_failed");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory ID: %d\n", shmid);

    buffer = (char *)shmat(shmid, NULL, 0);
    if (buffer == (char *)-1) {
        perror("shmat_failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter input: ");
    scanf("%s", buffer);

    return 0;
}
