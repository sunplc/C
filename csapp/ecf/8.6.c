#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[])
{
    puts("Command-line arguments:");
    char **argvp = argv;
    while (*argvp) {
        puts(*argvp);
        ++argvp;
    }

    puts("Environment variables:");
    char **envp = environ;
    while (*envp) {
        puts(*envp);
        ++envp;
    }

    return 0;
}
