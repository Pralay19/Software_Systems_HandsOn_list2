/* 
====================================
* PROGRAM: 27a.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to receive messages from the message queue.
a. with 0 as a flag
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
    char content[120];
};

int main() {
    struct container pkg;
    key_t token = ftok("../.",1);
    int channel = msgget(token, 0600 | IPC_CREAT);
    
    if (channel == -1) {
        perror("Channel creation failed");
        exit(1);
    }
    
    printf("Input your message:\n");
    pkg.flag = 3;
    fgets(pkg.content, 15, stdin);

    //we need to comment and uncomment these two lines below
    int send_status = msgsnd(channel, &pkg, sizeof(pkg.content), 0);
    if (send_status == -1) {
        perror("Transmission error");
    }
    

    int receive_status = msgrcv(channel, &pkg, sizeof(pkg.content), 3, 0);
    if (receive_status == -1) {
        perror("Reception error");
    } else {
        printf("Received content: %s", pkg.content);
    }

    return 0;
}