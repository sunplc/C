#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD_AMOUNT 10

int main()
{
    int childs[CHILD_AMOUNT] = {};
    int i;
    pid_t pid;

    for (i = 0; i < CHILD_AMOUNT; i++) {

        if ((pid = fork()) > 0) { // Parent
            childs[i] = pid;

        } else if (pid == 0) { // Child
            sleep(i);
            pid = getpid();
            printf("child %d terminated\n", pid);
            exit(0);

        } else { // fork error
            perror("fork error\n");
            exit(1);
        }
    }

    // reap child
    int status = 0;
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        printf("Reaping child %d\n", pid);
    }

    // if errno equals ECHILD, indicates waitpid terminated normally
    if (errno != ECHILD) {
        perror("waitpid error");
        exit(1);
    }

    printf("childs: [");
    for (i = 0; i < CHILD_AMOUNT; i++) {
        printf(" %d", childs[i]);
    }
    printf("]");

    return 0;
}

