#include <stdio.h>

int main(void)
{
    struct node {
        double item;
        struct node *next;
    };
    typedef struct node *link;
    link p = NULL;
    long ld = sizeof(*p);
    printf("%ld\n", ld);
    return 0;
}

