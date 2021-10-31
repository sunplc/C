#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

unsigned int wakeup(unsigned int secs)
{
    unsigned int remain = sleep(secs);

    printf("Slept for %d of %d secs.\n", secs - remain, secs);

    return remain;
}

void sigint_handler(int sig)
{
    printf("\nCaught SIGINT\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <secs>\n", argv[0]);
        exit(0);
    }

    signal(SIGINT, sigint_handler);
    wakeup(atoi(argv[1]));

    return 0;
}
