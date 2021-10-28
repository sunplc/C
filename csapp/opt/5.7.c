#include <stdio.h>

#include "vec.h"

#define IDENT 0
#define OP +


/* Implementation with maximum use of data abstraction */
void combine5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);

    data_t* data = get_vec_start(v);
    data_t acc = IDENT;

    for (i = 0; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}

/* 2 x 1 loop unrolling */
void combine5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=5) {
        acc = (acc OP data[i]);
        acc = (acc OP data[i+1]);
        acc = (acc OP data[i+2]);
        acc = (acc OP data[i+3]);
        acc = (acc OP data[i+4]);
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}

int main()
{
    data_t tmp;
    data_t *dest = &tmp;
    long len = 12000000;
    vec_ptr p = new_vec(len);
    combine1(p, dest);

    printf("*dest = %d\n", *dest);

    return 0;
}
