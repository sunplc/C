#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int hex2dd(char *hex, char *dd)
{
    if (!hex)
        return -1;

    unsigned int ip, tmp;
    ip = strtol(hex, NULL, 16);

    char *seg, *ptr;
    seg = (char *)malloc(4);
    ptr = dd;

    size_t bit_num = sizeof(ip) * 8;
    size_t length;
    int shift_bits;

    for (shift_bits = bit_num - 8; shift_bits >= 0; shift_bits -= 8) {
        tmp = (ip >> shift_bits) & 0xff;
        sprintf(seg, "%d", tmp);
        length = strlen(seg);
        strncpy(ptr, seg, length);
        ptr += length;
        strncpy(ptr, ".", 1);
        ptr += 1;
    }

    --ptr;
    *ptr = '\0';

    free(seg);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stdout, "Usage: %s <hex>", argv[0]);
        exit(0);
    }

    char *dd = (char *)malloc(16);
    hex2dd(argv[1], dd);

    printf("%s\n", dd);
    free(dd);

    return 0;
}
