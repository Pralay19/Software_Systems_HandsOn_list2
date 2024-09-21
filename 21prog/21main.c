/* 
====================================
* PROGRAM: 21main.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write two programs so that both can communicate by FIFO -Use two way communications.
====================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int p1 = mkfifo("ch1", 0777);
    int p2 = mkfifo("ch2", 0777);
    if (p1 == -1 || p2 == -1){
        perror("Channel creation failed");
    }
    char outmsg[500];
    printf("Input message for transmission:\n");
    scanf("%[^\n]", outmsg);
    int out = open("ch1", O_WRONLY);
    int in = open("ch2", O_RDONLY);
    if (out == -1 || in == -1){
        perror("Channel access failed");
        exit(1);
    }
    int sent = write(out, outmsg, sizeof(outmsg));
    if (sent == -1){ perror("Transmission failed"); exit(1);}
    char inmsg[500];
    int received = read(in, inmsg, sizeof(inmsg));
    if (received == -1){ perror("Reception failed"); exit(1);}
    printf("Message received from counterpart: %s\n", inmsg);
    return 0;
}