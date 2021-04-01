
#include <limits.h>

#define EXPR (double)LONG_MAX ^

double simplefunc(double x)
{
    return EXPR(x);
}
