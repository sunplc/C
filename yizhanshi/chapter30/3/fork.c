#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    pid_t pid;
    char *message;
    int n;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        message = "This is the child";
        n = 6;
    } else {
        message = "This is the parent";
        n = 3;
    }
    for (; n > 0; n--) {
        puts(message);
        sleep(1);
    }
    return 0;
}
