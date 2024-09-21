/* 
====================================
* PROGRAM: 29.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to remove the message queue.
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    int token = ftok("/var/tmp", 33);

    int q_desc = msgget(token, 0644 | IPC_CREAT);
    if(q_desc == -1) { 
        perror("Queue creation failed");
        exit(1);
    }

    printf("Assigned queue identifier: %d\n", q_desc);

    system("ipcs -q");

    int status = msgctl(q_desc, IPC_RMID, NULL);

    printf("Message queue successfully removed.\n");

    return 0;
}