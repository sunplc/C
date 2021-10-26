#include "../csapp.h"

void sigint_handler(int sig) // SIGINT handler
{
    printf("\nCaught SIGINT\n");
    exit(0);
}

int main()
{
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error!");

    pause();

    return 0;
}
