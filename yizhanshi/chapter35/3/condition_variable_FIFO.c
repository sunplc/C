// 习题1
// 将condition_variable.c中链表的访问顺序由FILO改为FIFO

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct msg {
    struct msg *prev;
    struct msg *next;
    int num;
};

struct msg *head;
struct msg *tail;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
    struct msg *mp;
    for (;;) {
        pthread_mutex_lock(&lock);
        while (tail == NULL) {
            pthread_cond_wait(&has_product, &lock);
        }

        mp = tail;
        if (tail->prev == NULL)
            head = tail = NULL;
        else
            tail = tail->prev;

        pthread_mutex_unlock(&lock);
        printf("Consume %d\n", mp->num);
        free(mp);
        sleep(rand() % 5);
    }
}

void *producer(void *p)
{
    struct msg *mp;
    for (;;) {
        mp = malloc(sizeof(struct msg));
        mp->num = rand() % 1000 + 1;
        printf("Produce %d\n", mp->num);
        pthread_mutex_lock(&lock);

        if (head == NULL) {
            head = tail = mp;
        } else {
            mp->next = head;
            head->prev = mp;
            head = mp;
        }

        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&has_product);
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

