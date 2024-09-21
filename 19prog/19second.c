/* 
====================================
* PROGRAM: 19second.c
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
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(){
    int result = mknod("my_pipe", S_IFIFO | 0666, 0);
    if (result == -1){
        perror("PIPE creation failed");
        exit(1);
    }
    result = mkfifo("fifo_pipe", 0666);
    if (result == -1){
        perror("FIFO creation failed");
        exit(1);
    }
    printf("\n");
    int status=system("ls -l");
    return 0;
}