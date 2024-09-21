/* 
====================================
* PROGRAM: 22.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<fcntl.h>

int main() {
    fd_set inputset;
    struct timeval timeout;
    int status = mkfifo("datapipe", 0666);
    if(status == -1){ perror("Pipe creation failed"); }
    int pipe = open("datapipe", O_RDONLY|O_NONBLOCK);
    FD_ZERO(&inputset);
    FD_SET(pipe, &inputset);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0; 
    status = select(pipe + 1, &inputset, NULL, NULL, &timeout);
    if(status == -1){
        perror("Selection error");
    }
    else if (status){
        printf("Data received within 10 second window\n");
        exit(1);
    }
    else{
        printf("No data received\n");
        exit(1);
    }
    close(pipe);
    return 0;
}