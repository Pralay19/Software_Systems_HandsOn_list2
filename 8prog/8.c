/* 
====================================
* PROGRAM: 8.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void sig_handler(int sig) {
    if (sig == SIGSEGV) {
        printf("Segmentation fault signal\n");
        exit(0);
    } else if (sig == SIGINT) {
        printf("Received interrupt\n");
        exit(0);
    } else if (sig == SIGFPE) {
        printf("Received floating point error interrupt\n");
        exit(0);
    } else if (sig == SIGALRM) {
        printf("Received real timer signal\n");
        exit(0);
    } else if (sig == SIGVTALRM) {
        printf("Received virtual time signal\n");
        exit(0);
    } else if (sig == SIGPROF) {
        printf("Received profiling timer signal\n");
        exit(0);
    } else {
        exit(0);
    }
}

int main() {
signal(SIGSEGV, sig_handler);
signal(SIGINT, sig_handler);
signal(SIGFPE, sig_handler);
signal(SIGALRM, sig_handler);
signal(SIGVTALRM, sig_handler);
signal(SIGPROF, sig_handler);
int opr;
scanf("%d", &opr);
switch (opr) {
    case 1:
        {int *p = NULL;
        *p = 0;
        break;}
    case 2:
        {printf("Type Ctrl+C\n");
        while (1) {}
        break;}
    case 3:
        {int res = 0/0;
        break;}
    case 4:
        {printf("Using alarm system call\n");
        alarm(2);
        while (1) {}
        break;}
    case 5: {
        struct itimerval tm1;
        tm1.it_value.tv_sec = 5;
        tm1.it_value.tv_usec = 0;
        tm1.it_interval.tv_sec = 2;
        tm1.it_interval.tv_usec = 0;

        printf("Using setitimer (ITIMER_REAL)\n");
        setitimer(ITIMER_REAL, &tm1, NULL);
        while (1) {}
        break;
    }
    case 6: {
        struct itimerval tm2;
        tm2.it_value.tv_sec = 5;
        tm2.it_value.tv_usec = 0;
        tm2.it_interval.tv_sec = 2;
        tm2.it_interval.tv_usec = 0;
        setitimer(ITIMER_VIRTUAL, &tm2, NULL);
        while (1) {}
        break;
    }
    case 7: {
        struct itimerval tm3;
        tm3.it_value.tv_sec = 5;
        tm3.it_value.tv_usec = 0;
        tm3.it_interval.tv_sec = 2;
        tm3.it_interval.tv_usec = 0;
        setitimer(ITIMER_PROF, &tm3, NULL);
        while (1) {}
        break;
    }
}
return 0;
}
