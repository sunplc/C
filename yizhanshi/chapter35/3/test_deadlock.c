/* 测试多个线程间有多个互斥锁并且不按相同的锁顺序锁定时，产生死锁的情况 */
// 线程a锁定了锁1未释放，然后尝试锁定锁2，此时线程b已经锁定了锁2未释放，然后在尝试锁定锁1;
// 结果线程a和b都被阻塞了，就会发生死锁的情况

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 初始化两个线程互斥锁
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *);
void *doit2(void *);

int main()
{
    //创建两个线程类型 
    pthread_t ta, tb;

    //创建线程，设置线程id、线程属性、调用方法和传入调用方法的参数
    pthread_create(&ta, NULL, &doit, NULL);
    //pthread_create(&tb, NULL, &doit, NULL);
    pthread_create(&tb, NULL, &doit2, NULL);

    pthread_join(ta, NULL); //等待线程返回，让指定的线程开始执行
    pthread_join(tb, NULL);
    return 0;
}

void *doit(void *arg)
{
    pthread_t tid = pthread_self();
    printf("tid = %u(0x%x)\n", (unsigned int)tid, (unsigned int)tid);

    pthread_mutex_lock(&m1);
    sleep(3); //延时3秒，避免程序执行太快，而不会发生死锁(线程a去锁定锁2时，线程b还没有锁定锁2)
    pthread_mutex_lock(&m2);
    //sleep(3);
    pthread_mutex_unlock(&m2); 
    pthread_mutex_unlock(&m1);

    return NULL;
}

void *doit2(void *arg)
{
    pthread_t tid = pthread_self();
    printf("tid = %u(0x%x)\n", (unsigned int)tid, (unsigned int)tid);

    pthread_mutex_lock(&m2);
    //sleep(3);
    pthread_mutex_lock(&m1);
    //sleep(3);
    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);

    return NULL;
}
