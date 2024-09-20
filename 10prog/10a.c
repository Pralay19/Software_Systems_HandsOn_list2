/* 
====================================
* PROGRAM: 10a.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void handle_signal(int sig){
    if(sig==SIGSEGV){
        printf("Memory access violation detected\n");
        exit(1);
    }
}

int main(){
    struct sigaction act;
    act.sa_handler = handle_signal;
    act.sa_flags = 0;
    if(sigaction(SIGSEGV, &act, NULL) == -1){
        perror("Signal handling failed\n");
        exit(1);
    }
    int *ptr = NULL;
    *ptr = 100;
    return 0;
}