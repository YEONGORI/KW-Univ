#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <time.h>

#define MAX_PROCESSES 64

pid_t gettid(void) {
    return syscall(__NR_gettid);
}

void cleanup_func(void *arg) {
    printf("%s\n", (char *)arg);
}

void thread_func(void *arg) {
    int i;

    pthread_cleanup_push(cleanup_func, "first cleanup");
    pthread_cleanup_push(cleanup_func, "second cleanup");

    printf("$tid[%d] start\n", (int)arg);
    printf("$tid[%d] gettid = %ld\n", (int)arg, (unsigned long)gettid());
    printf("$tid[%d] getpid = %ld\n", (int)arg, (unsigned long)getpid());

    for (i=0; i<0x40000000; i++);
    if ((int)arg == 0)
        pthread_exit(0);

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void *)1;
}

int main(void) {
    pthread_t tid[MAX];

    pthread_create(&tid[0], NULL, thread_func, (void *) 0);
    pthread_create(&tid[1], NULL, thread_func, (void *) 1);

    printf("main    gettid = %ld\n", (unsigned long)gettid());
    printf("main    getpid = %ld\n", (unsigned long)getpid());

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}