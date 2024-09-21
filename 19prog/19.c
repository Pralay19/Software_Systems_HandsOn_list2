/* 
====================================
* PROGRAM: 19.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
====================================
*/
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    printf("Command: mknod myPipe1 p\n");
    char * a="mknod myPipe1 p";
    int status = system(a);
    if (status == 0) {
        //printf("Command mknod executed successfully.\n");
    } else {
        printf("Command mknod failed.\n");
    }
sleep(3);
printf("Command: mkfifo myPipe2 p\n");
    char *b="mkfifo myPipe2 p";
    int status1=system(b);
    if (status1 == 0) {
        //printf("Command mkfifo executed successfully.\n");
    } else {
        printf("Command mkfifo failed.\n");
    }
sleep(3);
printf("Command: ls\n");
    char *c="ls";
    int status2=system(c);
sleep(3);
printf("Command: strace -c mkfifo myPipe3\n");
    char *d="strace -c mkfifo myPipe3";
    int status3=system(d);
    if (status3 == 0) {
        //printf("Command strace executed successfully.\n");
    } else {
        printf("Command strace failed.\n");
    }
sleep(3);
printf("Command: strace -c mknod myPipe4 p\n");
    char *e="strace -c mknod myPipe4 p";
    int status4=system(e);
    if (status4 == 0) {
        //printf("Command strace executed successfully.\n");
    } else {
        printf("Command strace failed.\n");
    }
}