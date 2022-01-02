#include "../csapp.h"

/* Global variables */
int readcnt;    /* Initially = 0 */
sem_t mutex, w; /* Both initially = 1 */

int value;

void *reader(void *p)
{
    while (1) {
        P(&mutex);
        readcnt++;
        if (readcnt == 1) /* First in */
            P(&w);
        V(&mutex);

        /* Critical section */
        printf("reader: value = %d\n", value);
        /* Reading happens  */

        P(&mutex);
        readcnt--;
        if (readcnt == 0) /* Last out */
            V(&w);
        V(&mutex);
    }
}

void *writer(void *p)
{
    static int x = 0;
    while (1) {
        P(&w);
        /* Critical section */
        value = ++x;
        printf("writer: value = %d\n", value);
        /* Writing happens  */
        V(&w); 
    }
}

int main() {
    readcnt = 0;
    Sem_init(&w, 0, 1);
    Sem_init(&mutex, 0, 1);

    pthread_t tid1, tid2;

    Pthread_create(&tid1, NULL, reader, (void *)NULL);
    Pthread_create(&tid2, NULL, writer, (void *)NULL);

    Pthread_join(tid1, NULL);
}