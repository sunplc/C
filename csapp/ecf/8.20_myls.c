#include "../csapp.h"

int main(int argc, char *argv[])
{
    setenv("COLUMNS", "20", 1);

    puts("Environment variables:");
    char **envp = environ;
    while (*envp) {
        puts(*envp);
        ++envp;
    }

    // environment variable COLUMNS not work for ls command. why is that?
    char *cmd = "/bin/ls";
    if (execve(cmd, argv, environ) < 0) {
        perror("execve error");
        exit(1);
    }

    return 0;
}
