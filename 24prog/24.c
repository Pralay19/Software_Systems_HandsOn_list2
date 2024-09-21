/* 
====================================
* PROGRAM: 24.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
 Write a program to create a message queue and print the 
key and message queue id.
====================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>

int main(void) {
    int token = ftok("/tmp", 65);
    if (token == -1){
        perror("failed");
        return 1;
    }
    int queue_id = msgget(token, IPC_CREAT | 0777);
    if(queue_id == -1){
        perror("Queue creation failed");
        return 1;
    }
    printf("Token: %d\n", token);
    printf("Queue Id: %d\n", queue_id);
    return 0;
}
