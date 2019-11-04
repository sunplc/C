#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void perror_exit(char *str)
{
    perror(str);
    exit(-1);
}

void *check_malloc(long size)
{
    void * ptr = malloc(size);
    if (ptr == NULL) {
        perror_exit("malloc failed!");
    }

    return ptr;
}

pthread_t *make_thread(void *(*entry)(void *), void *arg)
{
    pthread_t *tid = (pthread_t *)check_malloc(sizeof(pthread_t));
    if (pthread_create(tid, NULL, entry, arg) != 0) {
        perror_exit("make_thread failed");
    }

    return tid;
}

void join_thread(pthread_t *tid)
{
    if (pthread_join(*tid, NULL) != 0) {
        perror_exit("pthread_join failed");
    }
}

void exit_thread()
{
    pthread_exit(NULL);
}
