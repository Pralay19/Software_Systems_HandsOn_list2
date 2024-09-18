/* 
====================================
* PROGRAM: 5.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.
====================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {

printf("a) %ld\n", sysconf(_SC_ARG_MAX));
printf("b) %ld\n", sysconf(_SC_CHILD_MAX));
printf("c) %ld\n", sysconf(_SC_CLK_TCK));
printf("d) %ld\n", sysconf(_SC_OPEN_MAX));
printf("e) %ld\n", sysconf(_SC_PAGESIZE));
printf("f) %ld\n", sysconf(_SC_PHYS_PAGES));
printf("g) %ld\n", sysconf(_SC_AVPHYS_PAGES));

return 0;
}