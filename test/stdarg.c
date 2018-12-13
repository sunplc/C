#include <stdio.h>
#include <stdarg.h>

double average(int count, ...)
{
    va_list valist;
    va_start(valist, count);

    int i;
    double sum;
    for (i = 0; i < count; ++i) {
        sum += va_arg(valist, double);
    }

    return sum / count;
}

int main(int argc, char *argv[])
{

    printf("Average = %f\n", average(4, 1.2, 1.3, 1.4, 1.5));

	return 0;
}

