#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#include "utils.h"

typedef struct {
    int *array;
    int length;
    int next_in;
    int next_out;

    Sem *mutex;
    Sem *items;
    Sem *spaces;
} Queue;

Queue *make_queue(int length)
{
    Queue *queue = (Queue *)check_malloc(sizeof(Queue));
    queue->length = length;
    queue->array = (int *)check_malloc(sizeof(int) * length);
    queue->next_in = 0;
    queue->next_out = 0;

    queue->mutex = make_semaphore(1);
    queue->items = make_semaphore(0);
    queue->spaces = make_semaphore(length - 1);

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
    semaphore_wait(queue->spaces);
    semaphore_wait(queue->mutex);

    queue->array[queue->next_in] = value;
    queue->next_in = queue_incr(queue, queue->next_in);

    semaphore_signal(queue->mutex);
    semaphore_signal(queue->items);
}

int queue_pop(Queue *queue)
{
    semaphore_wait(queue->items);
    semaphore_wait(queue->mutex);

    int value = queue->array[queue->next_out];
    queue->next_out = queue_incr(queue, queue->next_out);

    semaphore_signal(queue->mutex);
    semaphore_signal(queue->spaces);

    return value;
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

int p_count = 0;
int c_count = 0;

void *producer_entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    int i;
    for (i = 0; i < shared->queue->length - 1; i++) {
        //printf("adding item %d\n", i);
        queue_push(shared->queue, i);
        ++p_count;
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
        ++c_count;
        //printf("consuming item %d\n", item);
    }

    exit_thread();
    return NULL;
}

int main(int argc, char *argv[])
{
    Shared *shared = make_shared(100000);

    pthread_t *t1 = make_thread(producer_entry, shared);
    pthread_t *t2 = make_thread(consumer_entry, shared);

    join_thread(t1);
    join_thread(t2);

    printf("product times: %d, consume times: %d\n", p_count, c_count);

    return 0;
}

