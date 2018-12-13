#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("useage: ./getenv home\n");
        exit(1);
    }
    char *name = argv[1];
    char *value = getenv(name);
    if (value != NULL) {
        puts(value);        
    } else {
        printf("No environment variable named \"%s\".\n", name);
    }
}
