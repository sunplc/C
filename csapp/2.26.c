#include <stdio.h>

size_t strlen(const char* s);

int strlonger(char* s, char *d)
{
    //printf("%X\n", (unsigned) (strlen(s) - strlen(d)));
    //return strlen(s) - strlen(d) > 0;
    return strlen(s) > strlen(d);
}

int main(int argc, char* argv[]) {

    char *s = "aaa";
    char *d = "bbbbb";
    printf("strlonger() result is %d\n", strlonger(s, d));

}

