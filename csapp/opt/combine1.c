#include <stdio.h>

#include "vec.h"

#define IDENT 0
#define OP +


/* Implementation with maximum use of data abstraction */
void combine1(vec_ptr v, data_t *dest)
{
    long i;

    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
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
