/* 
====================================
* PROGRAM: 11.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to ignore a SIGINT signal then reset 
the default action of the SIGINT signal - use sigaction system call.
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(){
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    act.sa_flags = 0;
    printf("Ignoring termination signal\n");
    if(sigaction(SIGINT, &act, NULL) == -1){
        perror("Signal setup failed");
        exit(1);
    }
    for(int count=0; count<6; count++){
        printf("%d seconds remaining\n", 5-count);
        sleep(1);
    }
    printf("Restoring default behavior\n");
    act.sa_handler = SIG_DFL;
    if(sigaction(SIGINT, &act, NULL) == -1){
        perror("Signal restoration failed");
        exit(1);
    }
    for(;;){};
    return 0;
}