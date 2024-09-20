/* 
====================================
* PROGRAM: 18.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
int fd_pipe1[2], fd_pipe2[2];

if (pipe(fd_pipe1) == -1 || pipe(fd_pipe2) == -1) {
    perror("pipe_error");
    exit(EXIT_FAILURE);
}

if (fork()) {
    sleep(1);
    close(fd_pipe2[0]);
    close(fd_pipe2[1]);
    close(fd_pipe1[0]);

    dup2(fd_pipe1[1], STDOUT_FILENO);  // Redirect stdout to fd_pipe1[1]
    char *ls_args[] = {"ls", "-l", NULL};
    execv("/bin/ls", ls_args);

    close(fd_pipe1[1]);
    wait(NULL);
} 
else {
    if (fork()) {
        sleep(1);
        close(fd_pipe1[1]);
        close(fd_pipe2[0]);

        dup2(fd_pipe1[0], STDIN_FILENO);  // Redirect stdin to fd_pipe1[0]
        dup2(fd_pipe2[1], STDOUT_FILENO); // Redirect stdout to fd_pipe2[1]
        char *grep_args[] = {"grep", "^d", NULL};
        execv("/bin/grep", grep_args);

        close(fd_pipe2[1]);
        close(fd_pipe1[0]);
        wait(NULL);
    } 
    else {
        close(fd_pipe1[0]);
        close(fd_pipe1[1]);
        close(fd_pipe2[1]);

        dup2(fd_pipe2[0], STDIN_FILENO);  // Redirect stdin to fd_pipe2[0]
        char *wc_args[] = {"wc", NULL};
        execv("/bin/wc", wc_args);

        close(fd_pipe2[0]);
    }
}

return 0;
}
