/* 
====================================
* PROGRAM: 25.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
====================================
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main() {

    key_t msg_key = ftok(".", 1);
    int msg_id = msgget(msg_key, IPC_CREAT | 0777);
    
    if (msg_id == -1) {
        perror("msgget() failed");
        exit(EXIT_FAILURE);
    }

    struct msqid_ds msg_info;
    if (msgctl(msg_id, IPC_STAT, &msg_info) == -1) {
        perror("msgctl_failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Access permission: %d\n", msg_info.msg_perm.mode);
    printf("UID: %d\t GID: %d\n", msg_info.msg_perm.uid, msg_info.msg_perm.gid);
    printf("Time of last message sent: %ld\n", msg_info.msg_stime);
    printf("Time of last message received: %ld\n", msg_info.msg_rtime);
    printf("Time of last queue change: %ld\n", msg_info.msg_ctime);
    printf("Current queue size (bytes): %ld\n", msg_info.__msg_cbytes);
    printf("Number of messages in queue: %ld\n", msg_info.msg_qnum);
    printf("Maximum queue size (bytes): %ld\n", msg_info.msg_qbytes);
    printf("Last msgsnd PID: %d\n", msg_info.msg_lspid);
    printf("Last msgrcv PID: %d\n", msg_info.msg_lrpid);

    return 0;
}


