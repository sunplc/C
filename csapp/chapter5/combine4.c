#include <stdio.h>

#include "vec.h"

#define IDENT 0
#define OP +


/* Implementation with maximum use of data abstraction */
void combine1(vec_ptr v, data_t *dest)
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
