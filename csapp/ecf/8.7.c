#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

unsigned int wakeup(unsigned int secs)
{
    unsigned int remain = sleep(secs);
    if (remain > 0) {
        printf("Slept for %d of %d secs.\n", secs - remain, secs);
    }
    return remain;
}

void sigint_handler(int sig)
{
    printf("\nCaught SIGINT\n");
}

int main(int argc, char *argv[])
{
    unsigned int secs;
    char * arg2;

    if (argc >= 2) {
        arg2 = argv[1];
        secs = atoi(arg2);
        if (secs > 0) {
            printf("sleep %d seconds...\n", secs);

            signal(SIGINT, sigint_handler);
            wakeup(secs);
        }
    }
}
