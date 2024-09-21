/* 
====================================
* PROGRAM: 27b.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to receive messages from the message queue.
b. with IPC_NOWAIT as a flag
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct container {
    long flag;
    char data[150];
};

int main() {
    struct container pkg;
    key_t token = ftok("/var/tmp", 65);
    int channel = msgget(token, 0644 | IPC_CREAT);
    
    printf("Enter your message:\n");
    pkg.flag = 5;
    fgets(pkg.data, 15, stdin);

    //we need to comment and uncomment these two lines below
    // int send_result = msgsnd(channel, &pkg, sizeof(pkg.data), 0);
    // if (send_result == -1) {
    //     perror("Send operation failed");
    // }

    int receive_result = msgrcv(channel, &pkg, sizeof(pkg.data), 5, IPC_NOWAIT);
    if (receive_result == -1) {
        perror("Receive operation failed");
    } else {
        printf("Retrieved message: %s", pkg.data);
    }

    return 0;
}