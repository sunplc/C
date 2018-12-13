/* 实现sleep函数 */
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void sig_alarm(int signo)
{
    /* nothing to do */
}

unsigned int mysleep(unsigned int nsecs)
{
    struct sigaction newact, oldact;
    unsigned int unslept;

    newact.sa_handler = sig_alarm; // 设置信号的处理函数，使用回调的方式
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact); // 向内核注册一个新的指定信号的处理函数，并返回旧的处理函数

    alarm(nsecs); // nsecs秒后向调用进程发送SIGALRM信号
    pause(); //pause函数使调用进程挂起直到有信号递达

    unslept = alarm(0); // alarm(0) 会返回上个设置的闹钟的剩余时间
    sigaction(SIGALRM, &oldact, NULL);

    return unslept;
}

int main(void)
{
    int remain = 0;
    while(1) {
        remain = mysleep(2);
        printf("Two seconds passed, remaining seconds = %d\n", remain);
    }
	return 0;
}

