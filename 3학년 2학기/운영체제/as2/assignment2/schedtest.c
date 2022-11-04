#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define MAX_PROCESSES 100

int main(void) {
    int result = 0, status = 0, num1 = 0, num2 = 0;
    char buf = ' ';
    
    FILE *f;
    pid_t pid;
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if ((f = fopen("temp.txt", "rb")) == NULL)
        exit(0);

    pid_t p = fork();
    if (p == 0) {
        for (int i=0; i<MAX_PROCESSES; i++) {
            if ((pid = fork()) < 0)
                return 1;
            if (pid == 0) {
                fread(&buf, 1, 1, f);
                while (buf != '\n') {
                    num1 = (num1 * 10) + (buf - '0');
                    fread(&buf, 1, 1, f);
                }
                fread(&buf, 1, 1, f);
                while (buf != '\n') {
                    num2 = (num2 * 10) + (buf - '0');
                    fread(&buf, 1, 1, f);
                }
                exit(num1 + num2);
            }
            else {          
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
    printf("value of fork : %d\n", result);
    printf("%lf\n", (double)((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec))/1000000000);

    fclose(f);
    return 0;
}