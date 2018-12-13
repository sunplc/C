// 使用condition variable 实现 semaphore

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM 5

pthread_mutex_t blank_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t product_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t product_cond = PTHREAD_COND_INITIALIZER;

int blank_number = NUM;
int product_number = 0;

int queue[NUM];

void *producer(void *arg)
{
    int p = 0;
    while (1) {
        pthread_mutex_lock(&product_lock);
        while (blank_number <= 0) {
            pthread_cond_wait(&blank_cond, &product_lock);
        }
        queue[p] = rand() % 1000 + 1;
        printf("Product %d\n", queue[p]);
        blank_number -= 1;
        product_number += 1;
        pthread_mutex_unlock(&product_lock);
        pthread_cond_signal(&product_cond);
        p = (p + 1) % NUM;
        sleep(rand() % 5);
    }
}

void *consumer(void *arg)
{
    int c = 0;
    while (1) {
        pthread_mutex_lock(&blank_lock);
        while (product_number <= 0) {
            pthread_cond_wait(&product_cond, &blank_lock);
        }
        printf("Consume %d\n", queue[c]);
        queue[c] = 0;
        product_number -= 1;
        blank_number += 1;
        pthread_mutex_unlock(&blank_lock);
        pthread_cond_signal(&blank_cond);
        c = (c + 1) % NUM;
        sleep(rand() % 5);
    }
}

int main(void)
{
    pthread_t pid, cid;
    srand(time(NULL));
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
	return 0;
}

