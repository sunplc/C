#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int status;
    time_t t;

    printf("parent pid = %d\n", getpid());
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() error");
    } else if (pid == 0) {
        printf("child pid = %d\n", getpid());
        sleep(5);
        exit(1);
    }

    do {
        if ((pid = waitpid(pid, &status, WNOHANG)) == -1) {
            perror("wait() error");
        } else if (pid == 0) {
            time(&t);
            printf("child is still running at %s\n", ctime(&t));
            sleep(1);
        } else {
            if (WIFEXITED(status)) {
                printf("child exited with status of %d\n",
                        WEXITSTATUS(status));
            } else {
                puts("child did not exit successfully");
            }
        }
    } while (pid == 0);

	return 0;
}

