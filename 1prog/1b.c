/* 
====================================
* PROGRAM: 1a.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
b. ITIMER_VIRTUAL
====================================
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>

void timer_handler(int signal_type) {

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

}

int main(int argc, char* argv[]) {

struct itimerval timer;
signal(SIGVTALRM, timer_handler);

timer.it_value.tv_sec = 2;
timer.it_value.tv_usec = 0;
timer.it_interval.tv_sec = 5;
timer.it_interval.tv_usec = 0;

setitimer(ITIMER_VIRTUAL, &timer, NULL);

while (1) {
   for (long long i = 0; i < 1000000000; ++i);
        sleep(1);
}

return 0;
}