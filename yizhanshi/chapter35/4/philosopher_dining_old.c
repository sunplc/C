// 哲学家就餐问题
// 代码实现有问题，仅作参考，正确的看philosopher_dining.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define AMOUNT 5 //哲学家和筷子数量

// 初始化五个互斥锁，分别对应五个筷子
pthread_mutex_t lock_array[AMOUNT];

pthread_cond_t cond_array[AMOUNT];

int cond_flag_array[AMOUNT];

// 哲学家线程信息
struct pinfo {
    pthread_t tid; //线程id
    int num; //编号: 0,1...
    char name; //名称: 'A','B'...
};

void *dining(void *arg)
{
    struct pinfo *p = arg;
    //pthread_t tid = pthread_self();
    //printf("philosopher'name is %c, tid %u(0x%x)\n", 
            //p->name, (unsigned int)tid, (unsigned int)tid);
    int first = p->num;
    int second = first == AMOUNT - 1 ? 0 : first + 1;
    while (1) {
        pthread_mutex_lock(&lock_array[first]);
        pthread_mutex_lock(&lock_array[second]);
        while (cond_flag_array[first] != 0 || cond_flag_array[second] != 0) {
            pthread_cond_wait(&cond_array[first], &lock_array[first]);
            pthread_cond_wait(&cond_array[second], &lock_array[second]);
        }
        cond_flag_array[first] = 1;
        cond_flag_array[second] = 1;
        printf("Philosopher %c fetchs chopstick %d\n", p->name, first);
        printf("Philosopher %c fetchs chopstick %d\n", p->name, second);

        sleep(rand() % 5); //吃饭n微秒

        cond_flag_array[first] = 0;
        pthread_mutex_unlock(&lock_array[first]);
        pthread_cond_broadcast(&cond_array[first]);

        cond_flag_array[second] = 0;
        pthread_mutex_unlock(&lock_array[second]);
        pthread_cond_broadcast(&cond_array[second]);
        printf("Philosopher %c release chopstick %d %d\n", p->name, first, second);
    }
    return 0;
}

int main()
{
    struct pinfo *pinfo_array = calloc(AMOUNT, sizeof(struct pinfo));
    if (pinfo_array == NULL)
        perror("calloc:");

    pthread_mutex_t *lock_array = calloc(AMOUNT, sizeof(pthread_mutex_t));
    pthread_cond_t *cond_array = calloc(AMOUNT, sizeof(pthread_cond_t));
    int i;
    for (i = 0; i < AMOUNT; i++) {
        pthread_mutex_t lock;
        pthread_mutex_init(&lock, NULL);
        lock_array[i] = lock;

        pthread_cond_t cond;
        pthread_cond_init(&cond, NULL);
        cond_array[i] = cond;

        cond_flag_array[i] = 0;

        pinfo_array[i].num = i;
        pinfo_array[i].name = (char)(i + 65); // 'A','B'...
        printf("name = %c\n", i+65);
        pthread_create(&pinfo_array[i].tid, NULL, dining, &pinfo_array[i]);
    }

    for (i = 0; i < AMOUNT; i++) {
        printf("join %c\n", pinfo_array[i].name);
        pthread_join(pinfo_array[i].tid, NULL);
    }

    return 0;
}

