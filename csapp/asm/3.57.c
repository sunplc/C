// 汇编参数 gcc -S -mavx2 -O0 3.57.c

double funct3(int *ap, double b, long c, float *dp)
{
    float f1 = *dp;
    double d2 = (double) *ap;

    if (b > d2) {
        f1 = f1 * (float)c;
        return (double)f1;
    } else {
        f1 *= 2;
        return (double) (f1 + (float)c);
    }
}
