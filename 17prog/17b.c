/* 
====================================
* PROGRAM: 17b.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to execute ls -l | wc.
a. use dup2
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
int fd_pipe[2];

if (pipe(fd_pipe) == -1) {
    perror("pipe_error");
    exit(EXIT_FAILURE);
}

if (fork() == 0) {
    close(fd_pipe[0]);
    dup2(fd_pipe[1], STDOUT_FILENO);
    char *cmd_ls[] = {"ls", "-l", NULL};
    execv("/bin/ls", cmd_ls);
    close(fd_pipe[1]);
} 
else {
    close(fd_pipe[1]);
    dup2(fd_pipe[0], STDIN_FILENO);
    char *cmd_wc[] = {"wc", NULL};
    execv("/bin/wc", cmd_wc);
    close(fd_pipe[0]);
    wait(NULL);
}

return 0;
}
