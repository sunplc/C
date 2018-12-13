#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void daemonize(void)
{
    pid_t pid;
    /*
     * become a session leader to lost controlling TTY.
     */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) { /* parent */
        exit(0);
    }
    setsid();

    /*
     * change the current working directory to /root
     */
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }

    /*
     * Attach file descriptors 0, 1 and 2 to /dev/null
     */
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
}

int main(void)
{
    daemonize();
    while(1);
}
