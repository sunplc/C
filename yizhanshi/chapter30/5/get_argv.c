#include <stdio.h>
#include <string.h>

#define MAXARGC 10

void str_to_argv(char *command, char **av, int maxLen);

int main(void)
{
    char a[] = "gcc % -g -Wall -lm -o main aa bb cc dd";
    //char **myargv;
    char *myargv[MAXARGC];
    int maxLen = MAXARGC;
    str_to_argv(a, myargv, maxLen);
    int i;
    for (i=0; i < MAXARGC; i++) {
        //printf("mark\n");
        if (myargv[i] != NULL)
            printf("%d: %s\n", i, myargv[i]);
        else
            break;
    }
    return 0;
}

void str_to_argv(char *command, char **myargv, int maxLen)
{
    char *token, *str, *saveptr;

    int i = 0;
    for (str = command; token != NULL; str = NULL) {
        if (i >= maxLen)
            break;
        token = strtok_r(str, " ", &saveptr);
        myargv[i] = token;
        ++i;
    }
}
