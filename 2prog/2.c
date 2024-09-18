/* 
====================================
* PROGRAM: 
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to print the system resource limits. Use getrlimit system call.
====================================
*/
#include <stdio.h>
#include <sys/resource.h>

int showLimits(int res, char *label) {
    struct rlimit limit;
    int status = getrlimit(res, &limit);
    static int index = 1;
    if (status == 0) {
        printf("%d) %s\n", index, label);
        printf("Soft limit: %ld\n", limit.rlim_cur);
        printf("Hard limit: %ld\n", limit.rlim_max);
        index++;
    } else {
        perror("Error fetching limits");
    }
}

int main() {
    showLimits(RLIMIT_CPU, "CPU Time");
    showLimits(RLIMIT_FSIZE, "File Size");
    showLimits(RLIMIT_STACK, "Stack Size (Bytes)");
    showLimits(RLIMIT_DATA, "Data Segment Size");
    showLimits(RLIMIT_NOFILE, "Max Number of Files");
    showLimits(RLIMIT_AS, "Virtual Memory Size");
    showLimits(RLIMIT_NPROC, "Max Number of Processes");
    showLimits(RLIMIT_MEMLOCK, "Max Locked Memory (Bytes)");
    showLimits(RLIMIT_LOCKS, "Max Number of File Locks");
    showLimits(RLIMIT_SIGPENDING, "Max Number of Pending Signals");
    showLimits(RLIMIT_MSGQUEUE, "Max Message Queue Size (Bytes)");
    showLimits(RLIMIT_NICE, "Max Nice Value");
    showLimits(RLIMIT_RTPRIO, "Max Realtime Scheduling Priority");
    showLimits(RLIMIT_RTTIME, "Max Time in RT Mode");
}
