// int sem_init(sem_t *sem, int pshared, unsigned int value);
// int sem_wait(sem_t *sem);
// int sem_trywait(sem_t *sem);
// int sem_post(sem_t *sem);
// int sem_destroy(sem_t *sem);
//
// sem_init() 初始化一个semaphore变量，pshread参数为0表示信号量用于同一进程中的线程间同步，value参数表示可用资源的数量
// sem_wait() 获得资源，使semaphore变量减1，如果调用sem_wait()时semaphore已经是0，则挂起等待。如果不希望挂起则可以使用sem_trywait()。
// sem_post() 释放资源，使semaphore变量加1，同时唤醒挂起等待的线程
// sem_destroy() 用完semaphore变量后，调用本函数释放semaphore相关的资源
// semaphore用于同一进程间的线程同步时，相当于多个mutex互斥锁
// 我的疑惑：semaphore没有互斥锁，sem_t是否可以同时读写，例如：两个线程同时对一个sem_t调用sem_wait()和sem_post()，不会出错吗？

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5

int queue[NUM];
sem_t blank_number, product_number;

void *producer(void *arg)
{
    int p = 0;
    while (1) {
        sem_wait(&blank_number);
        queue[p] = rand() % 1000 + 1;
        printf("Produce %d\n", queue[p]);
        sem_post(&product_number);
        p = (p + 1) % NUM;
        sleep(rand() % 5);
    }
}

void *consumer(void  *arg)
{
    int c = 0;
    while (1) {
        sem_wait(&product_number);
        printf("Consume %d\n", queue[c]);
        queue[c] = 0;
        sem_post(&blank_number);
        c = (c + 1) % NUM;
        sleep(rand() % 5);
    }
}

int main()
{
    pthread_t pid, cid;
    sem_init(&blank_number, 0, NUM);
    sem_init(&product_number, 0, 0);
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    return 0;
}

