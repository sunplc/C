#include <stdio.h>

int is_little_endian()
{
    unsigned int i = 1;
    char *p = (char *) &i;
    if (*p > 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char* argv[])
{
    printf("is_little_endian() = %d\n",
            is_little_endian());

}

