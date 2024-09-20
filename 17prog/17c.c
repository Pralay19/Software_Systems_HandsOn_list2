/* 
====================================
* PROGRAM: 17c.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to execute ls -l | wc.
a. use fcntl
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
int fd_pipe[2];

if (pipe(fd_pipe) == -1) {
    perror("pipe_error");
    exit(EXIT_FAILURE);
}

if (fork() == 0) {
    close(fd_pipe[0]);
    if (fcntl(fd_pipe[1], F_DUPFD, STDOUT_FILENO) == -1) {
        perror("fcntl_error");
        exit(EXIT_FAILURE);
    }
    char *cmd_ls[] = {"ls", "-l", NULL};
    execv("/bin/ls", cmd_ls);
    close(fd_pipe[1]);
} 
else {
    close(fd_pipe[1]);
    if (fcntl(fd_pipe[0], F_DUPFD, STDIN_FILENO) == -1) {
        perror("fcntl_error");
        exit(EXIT_FAILURE);
    }
    char *cmd_wc[] = {"wc", NULL};
    execv("/bin/wc", cmd_wc);
    close(fd_pipe[0]);
    wait(NULL);
}

return 0;
}
