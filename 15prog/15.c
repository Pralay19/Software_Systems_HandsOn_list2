/* 
====================================
* PROGRAM: 15.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a simple program to send some data from parent to the child process.
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
int pipefds[2];
if (pipe(pipefds) == -1){
    perror("PIPE creation failed");
    exit(1);
}
if(fork() != 0){
    close(pipefds[0]);
    char message[100];
    printf("Parent process-> Enter message for child: \n");
    scanf("%[^\n]", message);
    int sent = write(pipefds[1], message, strlen(message));
    printf("Parent (PID %d) transmitted %d bytes\n", getpid(), sent);
    close(pipefds[1]);
}
else{
    close(pipefds[1]);
    char received[100];
    int bytes = read(pipefds[0], received, sizeof(received)-1);
    if (bytes > 0){
        received[bytes] = '\n';
    }
    printf("Child (PID %d, Parent PID %d) received %d bytes\n", getpid(), getppid(), bytes);
    printf("Message from Parent: %s\n", received);
    close(pipefds[0]);
}
}