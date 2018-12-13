#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NLOOP 5000

int counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *);

int main(void)
{
    pthread_t ta, tb, tc;

    // create thread
    pthread_create(&ta, NULL, &doit, NULL);
    pthread_create(&tb, NULL, &doit, NULL);
    pthread_create(&tc, NULL, &doit, NULL);

    // wait thread terminate
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    pthread_join(tc, NULL);
    return 0;
}

void *doit(void *arg)
{
    int i;
    for (i = 0; i < NLOOP; i++) {
        pthread_mutex_lock(&counter_mutex);
        ++counter;
        printf("%x: %d\n", (unsigned int)pthread_self(), counter);
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}
