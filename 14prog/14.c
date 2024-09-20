/* 
====================================
* PROGRAM: 14.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
char input[100];
char output[100];
int pipefds[2];
if (pipe(pipefds) == -1){
    perror("PIPE creation failed");
    exit(1);
}
printf("Enter message for transmission: \n");
scanf("%[^\n]", input);
int written = write(pipefds[1], input, strlen(input));
close(pipefds[1]);
int received = read(pipefds[0], output, written);
close(pipefds[0]);
printf("Transmitted message: %s\n", output);
return 0;
}