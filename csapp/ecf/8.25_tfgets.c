#include "../csapp.h"

jmp_buf jbuf;

void sigalrm_handler(int sig)
{
    /* Sio_puts("Caught signal SIGALRM\n"); */

    siglongjmp(jbuf, 1);
}

char *tfgets(char *s, int size, FILE *stream)
{
    if (sigsetjmp(jbuf, 1) == 0) {

        // install alarm handler
        if (Signal(SIGALRM, sigalrm_handler) == SIG_ERR)
            unix_error("signal error");

        // alarm self after 5 seconds
        alarm(5);

        return fgets(s, size, stream);

    } else {
        return NULL;
    }
}

int main()
{
    int size = 1024;
    char buf[size];

    char *input = tfgets(buf, size - 1, stdin);

    printf("input: %s\n", input);

    return 0;
}
