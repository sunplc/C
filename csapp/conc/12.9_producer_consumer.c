/*

Practice Problem 12.9 (solution page 1074)
Let p denote the number of producers, c the number of consumers, and n the buffer
 size in units of items. For each of the following scenarios, indicate whether 
 the mutex semaphore in sbuf_insert and sbuf_remove is necessary or not.

A. p=1,c=1,n>1 
B. p=1,c=1,n=1 
C. p>1,c>1,n=1

*/

#include "../csapp.h"
#include "sbuf.h"

void *producer(void *sp);
void *consumer(void *sp);

int total;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <num>\n", argv[0]);
        return 0;
    } else {
        total = atoi(argv[1]);
    }

    pthread_t tid1, tid2;

    sbuf_t *sp = Malloc(sizeof(sbuf_t));
    sbuf_init(sp, 2);

    Pthread_create(&tid1, NULL, producer, (void *)sp);
    Pthread_create(&tid2, NULL, consumer, (void *)sp);

    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    sbuf_deinit(sp);
}

void *producer(void *sp) {
    sp = (sbuf_t *)sp;
    int i, limit = total;
    long sum = 0;
    for (i = 0; i < limit; i++) {
        sbuf_insert(sp, i);
        sum += i;
    }
    printf("producer: sum = %ld\n", sum);
    return NULL;
}

void *consumer(void *sp) {
    sp = (sbuf_t *)sp;
    int i, limit = total;
    long sum = 0;
    for (i = 0; i < limit; i++) {
        sum += sbuf_remove(sp);
    }
    printf("consumer: sum = %ld\n", sum);
    return NULL;
}