/**
 *
 * wait() 是系统调用函数，系统会挂起当前调用wait的进程，
 * 检查该进程是否有子进程已结束，否则一直挂起该进程直到
 * 该进程有一个子进程结束才会返回，wait会将status设置 
 * 为已退出子进程的退出状态值
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#define WORKER_COUNT 5

int main(int argc, char *argv[])
{
    int status, i;

    printf("parent pid = %d\n", getpid());

    pid_t pid;

    for (i = 0; i < WORKER_COUNT; i++) {

        pid = fork();
        if (pid < 0) {
            perror("fork() error");

        } else if (pid == 0) {
            printf("child pid = %d\n", getpid());
            sleep(5);
            exit(1);
        }

    }

    for (i = 0; i < WORKER_COUNT; i++) {

        if ((pid = wait(&status)) == -1) {
            perror("wait() error");
        } else {
            if (WIFEXITED(status)) {
                printf("child [%d] exited with status of %d\n",
                        pid, WEXITSTATUS(status));
            } else {
                puts("child did not exit successfully");
            }
        }
    }

	return 0;
}

