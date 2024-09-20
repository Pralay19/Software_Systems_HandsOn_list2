/* 
====================================
* PROGRAM: 10c.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a separate program using sigaction system call to catch the following signals.
c. SIGFPE
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void manage_signal(int sig_value){
    if(sig_value==SIGFPE){
        printf("Floating Point Error\n");
        exit(1);
    }
}

int main(){
struct sigaction action;
action.sa_handler = manage_signal;
action.sa_flags = 0;
if(sigaction(SIGFPE, &action, NULL) == -1){
    perror("Signal handling setup failed\n");
    exit(1);
}
int result = 5/0;
return 0;
}