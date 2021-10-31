#include "../csapp.h"

#define N 2

int main()
{
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)
        if ((pid = Fork()) == 0) /* Child */
        {
            // address of main function
            char *addr_of_main_func = (char *)main;
            printf("%p\n", addr_of_main_func);
            // write to text segment, should cause an segment fault
            *addr_of_main_func = '\0';

            // code which will not be reach
            exit(100+i);
        }

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            char msg[100];
            sprintf(msg, "child %d terminated by signal %d",
                    pid, sig);
            psignal(sig, msg);
        } else {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
        unix_error("waitpid error");

    exit(0);
}
