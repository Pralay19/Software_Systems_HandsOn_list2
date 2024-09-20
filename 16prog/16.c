/* 
====================================
* PROGRAM: 16.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to send and receive data from parent to child vice versa. Use two way
communication.
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
int pipefd_parent_child[2], pipefd_child_parent[2];

if (pipe(pipefd_parent_child) == -1 || pipe(pipefd_child_parent) == -1) {
    perror("pipe");
    exit(0);
}

if (fork() != 0) {  // Parent process
    close(pipefd_parent_child[0]);
    close(pipefd_child_parent[1]);

    char *parent_msg = "Hello My Child! \n";
    int write_res = write(pipefd_parent_child[1], parent_msg, strlen(parent_msg) + 1);
    if (write_res == -1) {
        perror("write");
        exit(0);
    }

    char child_buf[100];
    int read_res = read(pipefd_child_parent[0], child_buf, sizeof(child_buf));
    if (read_res == -1) {
        perror("read");
        exit(0);
    }

    printf("Parent with pid %d reads: %s\n", getpid(), child_buf);

    close(pipefd_parent_child[1]);
    close(pipefd_child_parent[0]);

    wait(0);
} else {  // Child process
    close(pipefd_parent_child[1]);
    close(pipefd_child_parent[0]);

    char *child_msg = "Hello my dear Parent \n";
    int write_res = write(pipefd_child_parent[1], child_msg, strlen(child_msg) + 1);
    if (write_res == -1) {
        perror("write");
        exit(0);
    }

    char parent_buf[100];
    int read_res = read(pipefd_parent_child[0], parent_buf, sizeof(parent_buf));
    if (read_res == -1) {
        perror("read");
        exit(0);
    }

    printf("Child with pid %d and parent pid %d reads: %s\n", getpid(), getppid(), parent_buf);

    close(pipefd_parent_child[0]);
    close(pipefd_child_parent[1]);
}

return 0;
}
