/* 
====================================
* PROGRAM: 4.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to measure how much time is taken to execute 100 getppid ( ) system call. 
Use time stamp counter.
====================================
*/
#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h>

int main() {
unsigned long long t1, t2, dt;

t1 = __rdtsc();
for (int i = 0; i < 100; ++i) {
    getppid();
}
t2 = __rdtsc();
//My Processor frequency is 1800 Mhz.
printf("Time taken for 100 getppid(): %.2f ns\n", (t2 - t1) / (double)1.8);

return 0;
}