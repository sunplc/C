#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "utils.h"

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

Mutex *make_mutex()
{
    Mutex *mutex = (Mutex *) check_malloc(sizeof(Mutex));
    if (pthread_mutex_init(mutex, NULL) != 0) {
        perror_exit("pthread_mutex_init failed");
    }
    return mutex;
}

void mutex_lock(Mutex *mutex)
{
    if (pthread_mutex_lock(mutex) != 0) {
        perror_exit("pthread_mutex_lock failed");
    }
}

void mutex_unlock(Mutex *mutex)
{
    if (pthread_mutex_unlock(mutex) != 0) {
        perror_exit("pthread_mutex_unlock failed");
    }
}

Cond *make_cond()
{
    Cond *cond = (Cond *) check_malloc(sizeof(Cond));
    if (pthread_cond_init(cond, NULL) != 0) {
        perror_exit("pthread_cond_init failed");
    }
    return cond;
}

void cond_wait(Cond *cond, Mutex *mutex)
{
    if (pthread_cond_wait(cond, mutex) != 0) {
        perror_exit("pthread_cond_wait failed");
    }
}

void cond_signal(Cond *cond)
{
    if (pthread_cond_signal(cond) != 0) {
        perror_exit("pthread_cond_signal failed");
    }
}

Sem *make_semaphore(int counter)
{
    if (counter < 0) {
        perror_exit("make_semaphore counter less than zero");
    }

    Sem *sem = (Sem *)check_malloc(sizeof(Sem));
    sem->wakeups = 0;
    sem->counter = counter;
    sem->counter_mutex = make_mutex();
    sem->cond = make_cond();

    return sem;
}

void semaphore_wait(Sem *sem)
{
    mutex_lock(sem->counter_mutex);
    --sem->counter;

    if (sem->counter < 0) {
        do {
            cond_wait(sem->cond, sem->counter_mutex);
        } while (sem->wakeups < 1);
        --sem->wakeups;
    }

    mutex_unlock(sem->counter_mutex);
}

void semaphore_signal(Sem *sem)
{
    mutex_lock(sem->counter_mutex);
    ++sem->counter;

    if (sem->counter <= 0) {
        ++sem->wakeups;
        cond_signal(sem->cond);
    }

    mutex_unlock(sem->counter_mutex);
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
