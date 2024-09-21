/* 
====================================
* PROGRAM: 28.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to change the exiting message queue 
permission. (use msqid_ds structure)
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    int token = ftok(".", 4);

    int q_id = msgget(token, 0777 | IPC_CREAT);

    struct msqid_ds q_info;
    int status = msgctl(q_id, IPC_STAT, &q_info);
    if(status == -1) { 
        perror("Queue info retrieval failed");
        exit(1); 
    }

    printf("Initial access mode: %o\n", q_info.msg_perm.mode);

    q_info.msg_perm.mode = 0766;
    status = msgctl(q_id, IPC_SET, &q_info);
    if(status == -1) { 
        perror("Queue modification failed");
        exit(1); 
    }

    printf("Updated access mode: %o\n", q_info.msg_perm.mode);

    return 0;
}