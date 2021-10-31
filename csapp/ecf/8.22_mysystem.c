#include "../csapp.h"

// type "man system" on terminal to see Unix system function

int mysystem(char * command)
{
    pid_t pid = Fork();
    if (pid == 0) {
        if (execl("/bin/sh", "sh", "-c", command, (char *)NULL) < 0) {
            unix_error("execl fail:");
        }
    } else if (pid > 0) {
        int status = 0;
        wait(&status);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }

    return -1;
}

int main()
{
    char *cmd = "ls -altrh --time-style=long-iso";
    int ret = mysystem(cmd);
    printf("mysystem returns: %d\n", ret);

    return 0;
}
