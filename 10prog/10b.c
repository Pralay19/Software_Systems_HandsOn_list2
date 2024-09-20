/* 
====================================
* PROGRAM: 
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a separate program using sigaction system call to catch the following signals.
b. SIGINT
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void process_signal(int sig_type){
    if(sig_type==SIGINT){
        printf("\nTermination request received\n");
        exit(1);
    }
}

int main(){
struct sigaction action;
action.sa_handler = process_signal;
action.sa_flags = 0;
if(sigaction(SIGINT, &action, NULL) == -1){
    perror("Signal setup failed\n");
    exit(1);
}
printf("Use termination shortcut\n");
for(;;){};
return 0;
}