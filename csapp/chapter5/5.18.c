#include <stdio.h>
#include <sys/time.h>

double poly(double a[], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr = x; /* Equals x^i at start of loop */
    for (i = 1; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

double poly_optimized(double a[], double x, long degree)
{
    long i = 0, limit = degree - 4;
    double acc0 = a[0], acc1 = 0, acc2 = 0, acc3 = 0;

    double xpwr0 = x;   /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    
    for (i = 1; i <= limit; i+=4) {
        acc0 += a[i] * xpwr0;
        acc1 += a[i+1] * xpwr1;
        acc2 += a[i+2] * xpwr2;
        acc3 += a[i+3] * xpwr3;
        xpwr0 *= x;
        xpwr1 *= x;
        xpwr2 *= x;
        xpwr3 *= x;
    }

    for (; i <= degree; i++) {
        acc0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    return acc0 + acc1 + acc2 + acc3;
}

/* Apply Horner’s method */
double polyh(double a[], double x, long degree)
{
    long i;
    double result = a[degree];
    for (i = degree-1; i >= 0; i--)
        result = a[i] + x*result;
    return result;
}

int main(void)
{
    // this line may cause segment fault while len is too large, 
    // since function 'polyh' use recursive function call
    long i, len = 500000; 
    double a[len];
    for (i = 0; i < len; i++) {
        a[i] = i;
    }

    struct timeval start;
    struct timeval end;
    float timer;

    gettimeofday(&start,NULL); //结构体start当前时间（1970年1月1日到现在的时间）
    poly(a, 3.45, len-1);
    gettimeofday(&end,NULL);
    //计算start和end之间的时间差
    timer = end.tv_sec - start.tv_sec + (float)(end.tv_usec - start.tv_usec)/1000000;    
    printf("poly time:\n %fs\n",timer);


    gettimeofday(&start,NULL); //结构体start当前时间（1970年1月1日到现在的时间）
    poly_optimized(a, 3.45, len-1);
    gettimeofday(&end,NULL);
    //计算start和end之间的时间差
    timer = end.tv_sec - start.tv_sec + (float)(end.tv_usec - start.tv_usec)/1000000;    
    printf("poly_optimized time:\n %fs\n",timer);

    gettimeofday(&start,NULL); //结构体start当前时间（1970年1月1日到现在的时间）
    polyh(a, 3.45, len-1);
    gettimeofday(&end,NULL);
    //计算start和end之间的时间差
    timer = end.tv_sec - start.tv_sec + (float)(end.tv_usec - start.tv_usec)/1000000;    
    printf("polyh time:\n %fs\n",timer);
}
