/* 
====================================
* PROGRAM: 12.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(){

if (fork()==0){
    printf("Offspring process with parent ID %d\n", getppid());
    kill(getppid(), SIGKILL);
    sleep(5);
    printf("Chil process is now orphan having  new parent ID: %d\n", getppid());
}
else{
    printf("Progenitor executing\n");
    sleep(1);
    for(;;){};
}
}