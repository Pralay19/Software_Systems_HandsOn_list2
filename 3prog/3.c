/* 
====================================
* PROGRAM: 3.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to set (any one) system resource limit. Use setrlimit system call.
====================================
*/
#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;

    if (getrlimit(RLIMIT_CPU, &rl) == 0) {
        printf("CPU limit before\n");
        printf("Soft = %ld, Hard = %ld\n", rl.rlim_cur, rl.rlim_max);
    } else {
        perror("getrlimit");
    }

    rl.rlim_cur = 10;
    rl.rlim_max = 200;
    int rt = setrlimit(RLIMIT_CPU, &rl);
    if (rt == 0) {
        printf("CPU limit set successfully\n");
    } else {
        perror("setrlimit error");
    }

    if (getrlimit(RLIMIT_CPU, &rl) == 0) {
        printf("CPU limit after\n");
        printf("Soft = %ld, Hard = %ld\n", rl.rlim_cur, rl.rlim_max);
    } else {
        perror("getrlimit");
    }
}
