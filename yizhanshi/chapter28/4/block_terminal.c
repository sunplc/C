#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
    char buf[10];
    int n;
    printf("STDIN_FILENO = %d, STDOUT_FILENO = %d\n", STDIN_FILENO, STDOUT_FILENO);
    printf("EWOULDBLOCK = %d\n", EWOULDBLOCK); // errno.h
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        perror("read STDIO_FILENO");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    return 0;
}
