#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sched.h>

#define MAX_PROCESSES 30000

int main(void) {
    int status = 0;
    char buf = ' ';
    char num[100];
    
    FILE *f;
    pid_t pid;

    struct sched_param param;
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);


    // OTHER : can only be used at status priority 0
    param.sched_priority = 0;

    pid_t p = fork();
    if (p == 0) {
        for (int i=0; i<MAX_PROCESSES; i++) {
            char file_name[10000] = {'t','e','m','p','/','\0'};
            sprintf(num, "%d", i);
            FILE *f = fopen(strcat(file_name, num), "rb");
            if ((pid = fork()) < 0)
                return 1;
            sched_setscheduler(0, SCHED_OTHER, &param);
            // default nice
            if (pid == 0) {
                fread(&buf, 1, 1, f);
                exit(0);
            }
            else {          
                waitpid(pid, &status, 0);
            }
            fclose(f);
        }
        exit(0);
    }
    else {
        waitpid(p, &status, 0);
    }
    clock_gettime(CLOCK_REALTIME, &stop);
    time_t sec = stop.tv_sec - start.tv_sec;
    long nsec = stop.tv_nsec - start.tv_nsec;
    if (nsec < 0) nsec += 1000000000;
    printf("%lf\n", (double)(sec + nsec)/1000000000);
    return 0;
}
