/* 
====================================
* PROGRAM: 21side.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write two programs so that both can communicate by FIFO -Use two way communications.
====================================
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    char inmsg[500], outmsg[500];
    printf("Input message for transmission:\n");
    scanf("%[^\n]", outmsg);
    int in = open("ch1", O_RDONLY);
    int out = open("ch2", O_WRONLY);
    if (in == -1 || out == -1){
        perror("Channel access failed");
        exit(1);
    }
    int received = read(in, inmsg, sizeof(inmsg));
    if (received == -1){ perror("Reception failed"); exit(1);}
    printf("Message received from counterpart: %s\n", inmsg);
    int sent = write(out, outmsg, sizeof(outmsg));
    if (sent == -1){ perror("Transmission failed"); exit(1);}
    return 0;
}