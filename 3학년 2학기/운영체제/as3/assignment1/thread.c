#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#define MAX_PROCESSES 64

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
FILE *f;
int result;

void *thread_func(void *arg) {
    int num1 = 0, num2 = 0;
    char buf = ' ';

    pthread_mutex_lock(&lock);
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
    result += (num1 + num2);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t tid[MAX_PROCESSES];
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if ((f = fopen("temp.txt", "rb")) == NULL)
        return 1;
    for (int i=0; i<MAX_PROCESSES; i++)
        pthread_create(&tid[i], NULL, thread_func, NULL);

    for (int i=0; i<MAX_PROCESSES; i++)
        pthread_join(tid[i], NULL);

    clock_gettime(CLOCK_REALTIME, &stop);
    printf("value of fork : %d\n", result);
    printf("%lf\n", (double)((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec))/1000000000);

    fclose(f);
    return 0;
}