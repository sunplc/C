#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h> // sleep()

#include "utils.h"

typedef struct {
    int *array;
    int length;
    int next_in;
    int next_out;
} Queue;

Queue *make_queue(int length)
{
    Queue *queue = (Queue *)check_malloc(sizeof(Queue));
    queue->length = length;
    queue->array = (int *)check_malloc(sizeof(int) * length);
    queue->next_in = 0;
    queue->next_out = 0;

    return queue;
}

int queue_incr(Queue *queue, int i)
{
    return (i + 1) % queue->length;
}

int queue_empty(Queue *queue)
{
    return queue->next_in == queue->next_out;
}

int queue_full(Queue *queue)
{
    return queue_incr(queue, queue->next_in) == queue->next_out;
}

void queue_push(Queue *queue, int value)
{
    if (queue_full(queue)) {
        perror_exit("queue is full");
    }

    queue->array[queue->next_in] = value;
    queue->next_in = queue_incr(queue, queue->next_in);
}

int queue_pop(Queue *queue)
{
    if (queue_empty(queue)) {
        perror_exit("queue is empty");
    }

    int value = queue->array[queue->next_out];
    queue->next_out = queue_incr(queue, queue->next_out);

    return value;
}

void print_queue(Queue *queue)
{
    int i = queue->next_out;
    while (1) {
        printf("%d", queue->array[i]);

        if (i + 1 == queue->next_in) {
            break;
        }
        fputs(", ", stdout);

        if (i + 1 >= queue->length) {
            i = 0;
        } else {
            i++;
        }
    }
    putchar('\n');
}

typedef struct {
    Queue *queue;
} Shared;

Shared *make_shared(int length)
{
    Shared *shared = (Shared *)check_malloc(sizeof(Shared));
    shared->queue = make_queue(length);
    return shared;
}

// TEST CODE

void queue_test()
{
    int i;
    int item;
    int length = 128;

    Queue *queue = make_queue(length);
    assert(queue_empty(queue));
    for (i=0; i<length-1; i++) {
        queue_push(queue, i);
    }
    assert(queue_full(queue));
    for (i=0; i<10; i++) {
        item = queue_pop(queue);
        assert(i == item);
    }
    assert(!queue_empty(queue));
    assert(!queue_full(queue));
    for (i=0; i<10; i++) {
        queue_push(queue, i);
    }
    assert(queue_full(queue));
    for (i=0; i<10; i++) {
        item = queue_pop(queue);
    }  
    assert(item == 19);

    print_queue(queue);
}

void *test(void *p)
{
    puts("test function");
    return NULL;
}

void *producer_entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    int i;
    for (i = 0; i < shared->queue->length - 1; i++) {
        printf("adding item %d\n", i);
        queue_push(shared->queue, i);
    }

    exit_thread();
    return NULL;
}

void *consumer_entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    int i, item;
    for (i = 0; i < shared->queue->length - 1; i++) {
        item = queue_pop(shared->queue);
        printf("consuming item %d\n", item);
    }

    exit_thread();
    return NULL;
}

int main(int argc, char *argv[])
{
    //queue_test();
    Shared *shared = make_shared(10000);

    pthread_t *tid1= make_thread(producer_entry, shared);
    sleep(1);
    pthread_t *tid2 = make_thread(consumer_entry, shared);

    join_thread(tid1);
    join_thread(tid2);

    return 0;
}

