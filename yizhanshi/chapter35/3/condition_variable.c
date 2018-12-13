//pthread_cond_wait函数会立即释放互斥锁lock，然后阻塞当前线程，
//并等待条件变量信号到达，此时pthread_cond_wait函数还没有返回；
//当线程收到条件变量信号后，pthrea_cond_wait函数会继续执行，
//函数会重新尝试获取互斥锁lock，如果获取成功，函数会返回，
//如果获取失败，函数会继续阻塞等待lock释放后再去获取。
//
//pthread_cond_wait函数内部流程:
//pthread_cond_wait() {
//    pthread_mutex_unlock()
//    pthread_just_wait()
//    pthread_mutex_lock()
//}
//
//所以pthread_cond_wait函数必须位于pthread_mutex_lock和pthread_mutex_unlock之间。
//
//pthread_cond_wait函数返回之后，必须再次检查条件是否满足，
//因为wait函数收到信号后需要再次获取互斥锁lock，可能会失败阻塞一段时间，
//即使马上成功获取了lock，也可能还有其他的线程使条件又不满足了；
//还有可能有多个线程在等待条件变量信号，所以当前线程继续执行时，条件可能已经改变，
//所以必须再次检查条件，所以pthread_cond_wait外需要用while循环
//
//pthread_cond_signal
//会给一个线程发送条件变量信号（应该是优先级最高的那个，队列中的第一个）
//pthread_cond_broadcast
//会给所有等待信号的线程发送信号（会有一个等待队列）

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct msg {
    struct msg *next;
    int num;
};

struct msg *head;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
    struct msg *mp;
    for (;;) {
        pthread_mutex_lock(&lock);
        while (head == NULL) {
            pthread_cond_wait(&has_product, &lock);
        }
        mp = head;
        head = mp->next;
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
        mp->next = head;
        head = mp;
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

