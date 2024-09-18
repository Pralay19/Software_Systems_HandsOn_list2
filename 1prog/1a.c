/* 
====================================
* PROGRAM: 1a.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
a. ITIMER_REAL
====================================
*/
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>

// int elapsed_time = 0;
// int total_time = 0;
void timer_handler(int signal_type) {
//elapsed_time += 5;
switch(signal_type) {
    case SIGALRM:
        printf("SIGALRM received: Interval timer expired (ITIMER_REAL)\n");
        break;
    case SIGVTALRM:
        printf("SIGVTALRM received: Interval timer expired (ITIMER_VIRTUAL)\n");
        break;
    case SIGPROF:
        printf("SIGPROF received: Interval timer expired (ITIMER_PROF)\n");
        break;
    default:
        printf("Unknown signal received\n");
        break;
}
// if (elapsed_time >= total_time) {
//         printf("Program exiting after %d time.\n",total_time);
//         exit(0);  // Exit the program
// }
}

int main(int argc, char* argv[]) {
// printf("Enter a certain seconds: ");
// int t;
// scanf("%d ",&total_time);
struct itimerval timer;
signal(SIGALRM, timer_handler);

timer.it_value.tv_sec = 3;
timer.it_value.tv_usec = 0;
timer.it_interval.tv_sec = 10;
timer.it_interval.tv_usec = 10;

if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
    perror("Error in the timer");
    return 1;
}

while (1) {
    sleep(100);
}

return 0;
}