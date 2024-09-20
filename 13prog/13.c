/* 
====================================
* PROGRAM: 13.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not
====================================
*/
#include <stdio.h>
#include <signal.h>

int main() {
int processId;

printf("Enter process ID: ");
scanf("%d", &processId);

if (kill(processId, SIGSTOP) == 0) {
    printf("Signal sent\n");
} else {
    perror("Error sending signal");
}

return 0;
}