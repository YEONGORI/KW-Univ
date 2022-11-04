#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define MAX_PROCESSES 8

int main(void) {
    int result = 0, status = 0, tmp = 0, tmp2 = 0;
    char buf = ' ';
    
    FILE *f;
    pid_t pid;
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if ((f = fopen("temp.txt", "rb")) == NULL)
        exit(0);

    pid_t p = fork();
    if (p == 0) { // 
        for (int i=0; i<MAX_PROCESSES; i++) {
            if ((pid = fork()) < 0)
                return 1;
            if (pid == 0) {                  // child process
                fread(&buf, 1, 1, f);        // read one number
                while (buf != '\n') {
                    tmp = (tmp * 10) + (buf - '0');
                    fread(&buf, 1, 1, f);
                }
                fread(&buf, 1, 1, f);        // again read one number
                while (buf != '\n') {
                    tmp2 = (tmp2 * 10) + (buf - '0');
                    fread(&buf, 1, 1, f);
                }
                exit(tmp + tmp2);
            }
            else {                          // parent process
                waitpid(pid, &status, 0);
                result += (status >> 8);
            }
        }
        exit(result);
    }
    else {
        waitpid(p, &status, 0);
        result += (status >> 8);
    }
    clock_gettime(CLOCK_REALTIME, &stop);
    printf("%lf\n", (double)((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec))/1000000000);
    fclose(f);
    printf("%d\n", result);
}