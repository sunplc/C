#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t testlock;
pthread_t test_thread;

void *test()
{
    pthread_mutex_lock(&testlock);
    printf("thread Test()\n");
    pthread_mutex_unlock(&testlock);
}

int main()
{
    pthread_mutex_init(&testlock, NULL);

    pthread_mutex_lock(&testlock);
    printf("Main thread locked the testlock\n");

    pthread_create(&test_thread, NULL, test, NULL);
    //pthread_join(test_thread, NULL); // 如果主线程在这里等待 test_thread 线程返回，会造成死锁，因为主线程还没有释放锁，test_thread在test方法中获取锁会一直阻塞，主线程也会一直阻塞下去
    sleep(3);

    pthread_mutex_unlock(&testlock);
    printf("Main thread unlocked the testlock\n");

    sleep(1);
    pthread_join(test_thread, NULL);

    pthread_mutex_destroy(&testlock);
    return 0;
}

