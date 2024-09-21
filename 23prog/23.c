/* 
====================================
* PROGRAM: 23.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
 Write a program to print the maximum number of files can be opened 
within a process and size of a pipe (circular buffer).
====================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>

int main(void) {
    if(mkfifo("datapipe", S_IRWXU) == -1){
        perror("Pipe creation failed");
    }
    long fileLimit = sysconf(_SC_OPEN_MAX);
    if (fileLimit == -1){
        perror("System config query failed");
    }
    printf("Maximum concurrent open files: %ld\n", fileLimit);
    long pipeCapacity = pathconf("datapipe", _PC_PIPE_BUF);
    if (pipeCapacity == -1){
        perror("Path config query failed");
    }
    printf("Maximum pipe buffer capacity: %ld\n", pipeCapacity);
    return 0;
}