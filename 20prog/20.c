/* 
====================================
* PROGRAM: 20.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write two programs so that both can communicate by FIFO -Use one way communication.
====================================
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

int main(){
    char *ch = "data_pipe";
    int status = mkfifo(ch, 0666);
    if (status == -1){ perror("Pipe creation failed");}
    char message[100];
    printf("Enter message for transmission:\n");
    scanf("%[^\n]", message);
    int pipe = open(ch, O_WRONLY);
    if (pipe == -1){ perror("Pipe access failed"); exit(1);}
    int transmitted = write(pipe, message, strlen(message));
    if (transmitted == -1){ perror("Data transmission failed"); exit(1);}
    else{ printf("Bytes transmitted: %d\n", transmitted);}
    close(pipe);
    return 0;
}