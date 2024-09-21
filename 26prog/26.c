/* 
====================================
* PROGRAM: 26.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
 Write a program to send messages to the message queue. Check $ipcs -q
====================================
*/
#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>

struct Message {
    long type;
    char data[100];
}msg;

int main() {
    int messageKey = ftok(".", 1);
    int messageQueue = msgget(messageKey, 0666 | IPC_CREAT);

    if (messageQueue == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue ID: %d\n", messageQueue);

    msg.type = 1;

    fgets(msg.data, 10, stdin);

    int sendResult = msgsnd(messageQueue, &msg, sizeof(msg), 0);
    if (sendResult == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Data sent to message queue\n");

    return 0;
}