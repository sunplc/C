#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t gid = getpgrp();
    printf("origin group id = %d\n", gid);

    pid_t pid = fork();

    if (pid == 0) {
        gid = getpgrp();
        printf("child group id = %d\n", gid);
        exit(0);
    }


    gid = getpgrp();
    printf("parent group id = %d\n", gid);
    
    return 0;
}
