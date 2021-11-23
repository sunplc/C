#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int dd2hex(char *dd, char *hex)
{
    char *seg, *ptr, *ptr_copy, *endptr;   
    seg = (char *)malloc(4);
    unsigned int ip = 0;
    int length = strlen(dd);
    ptr = (char *)malloc(length);
    ptr_copy = ptr;
    memcpy(ptr, dd, length);

    while ((endptr = strchr(ptr, '.')) != NULL) {
        length = endptr - ptr + 1;
        *endptr = '\0';
        seg = strncpy(seg, ptr, length);
        ptr = endptr + 1;
        ip = (ip << 8) + atoi(seg);
    }

    // get the last segment
    endptr = strchr(ptr, '\0');
    length = endptr - ptr + 1;
    seg = strncpy(seg, ptr, length);
    ip = (ip << 8) + atoi(seg);

    sprintf(hex, "0x%x", ip);

    free((void *)ptr_copy);
    free((void *)seg);

    return 0;
}

int main(int argc, char **argv)
{

    if (argc != 2) {
        fprintf(stdout, "Usage: %s <dot seperated decimal>", argv[0]);
        exit(0);
    }

    char *hex = (char *)malloc(11);
    dd2hex(argv[1], hex);

    printf("hex = %s\n", hex);
    free(hex);

    return 0;
}
