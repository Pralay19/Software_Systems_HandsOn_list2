/* 
====================================
* PROGRAM: 9.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to ignore a SIGINT signal then reset the default 
action of the SIGINT signal - Use signal system call.
====================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[]) {
printf("Ignoring Ctrl+C\n");
signal(SIGINT, SIG_IGN);
int seconds=strtol(argv[1], NULL, 10);
for (int t = seconds; t > 0; t--) {
    printf("\n %d seconds left\n", t);
    fflush(stdout);
    sleep(1);
}

printf("Default action triggered\n");
signal(SIGINT, SIG_DFL);

while (1) {}
}