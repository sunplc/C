#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAXLINE 80

int main(void)
{
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    //父进程读取了自己写入管道的信息;子进程先读取管道后写入管道，因为管道中没有数据，所以一直被阻塞。
    if (pid > 0) {
        printf("parent process.\n");

        printf("parent input:\n");
        n = read(STDIN_FILENO, line, MAXLINE);
        write(fd[1], line, n);

        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, "parent:", 7);
        write(STDOUT_FILENO, line, n);

        wait(NULL);
    } else {
        printf("child process.\n");

        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, "child:", 6);
        write(STDOUT_FILENO, line, n);

        printf("child input:\n");
        n = read(STDIN_FILENO, line, MAXLINE);
        write(fd[1], line, n);
    }
    return 0;
}
