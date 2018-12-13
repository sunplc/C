#include <stdio.h>
#include <unistd.h>

int main(void)
{
    //设定10分钟的闹钟，10分钟后会给当前进程发送SIGALRM信号
    alarm(600);
    int i;
    // 睡眠30秒
    for (i=0; i < 30; i++)
        sleep(1);
    int remain = alarm(0);
    printf("remain seconds %d\n", remain);
	return 0;
}

