// 哲学家就餐问题

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define AMOUNT 5 //哲学家和筷子数量

// 哲学家线程信息
struct pinfo {
    pthread_t tid;	//线程id
    int num;		//哲学家编号: 0,1...
    char name;		//哲学家名字: 'A','B'...
    int times;		//累计的吃饭次数
};

// 定义五个互斥锁，分别对应五个筷子
pthread_mutex_t lock_array[AMOUNT];

void *dining(void *arg)
{
    struct pinfo *p = arg;

    int left = p->num; //左边的筷子编号
    int right = left == AMOUNT - 1 ? 0 : left + 1; //右边的筷子编号

    int i = 0;
    while (i < 1000) { //吃饭n次
        pthread_mutex_lock(&lock_array[left]);
        if (pthread_mutex_trylock(&lock_array[right]) != 0) {
            pthread_mutex_unlock(&lock_array[left]);
            continue;
        }

        printf("Phi %c fetchs chopstick %d\n", p->name, left);
        printf("Phi %c fetchs chopstick %d\n", p->name, right);

        usleep(rand() % 1000); //吃饭n微秒

        pthread_mutex_unlock(&lock_array[left]);
        pthread_mutex_unlock(&lock_array[right]);
        p->times = p->times + 1;
        printf("Phi %c release chopstick %d %d, dining %d times.\n",
			p->name, left, right, p->times);

        ++i;
    }
    return 0;
}

int main()
{
    struct pinfo *pinfo_array = calloc(AMOUNT, sizeof(struct pinfo));
    if (pinfo_array == NULL)
        perror("calloc:");

    pthread_mutex_t *lock_array = calloc(AMOUNT, sizeof(pthread_mutex_t));
    if (lock_array == NULL)
        perror("calloc:");

    int i;
    for (i = 0; i < AMOUNT; i++) {
        pinfo_array[i].num = i;
        pinfo_array[i].name = (char)(i + 65); // 'A','B'...
        pinfo_array[i].times = 0;
        pthread_create(&pinfo_array[i].tid, NULL, dining, &pinfo_array[i]);

        pthread_mutex_t lock;
        pthread_mutex_init(&lock, NULL);
        lock_array[i] = lock;
    }

    for (i = 0; i < AMOUNT; i++) {
        pthread_join(pinfo_array[i].tid, NULL);
        printf("Phi %c thread end.\n", pinfo_array[i].name);
    }

    free(pinfo_array);
    free(lock_array);
    return 0;
}

