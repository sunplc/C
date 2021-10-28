

void merge(long src1[], long src2, long dest[], long n) {
    long i1 = 0;
    long i2 = 0;
    long id = 0;
    long tmp = 0;
    long tmp1 = 0;
    long tmp2 = 0;
    long take = 0;
    while (i1 < n && i2 < n) {
        tmp1 = src1[i1];
        tmp2 = src2[i2];

        take = src1[i1] < src2[i2];
        tmp =  take ? tmp1 : tmp2; 
        dest[id++] = tmp;

        i1 += take;
        i2 += (1-take);
    }
    while (i1 < n)
        dest[id++] = src1[i1++];
    while (i2 < n)
        dest[id++] = src2[i2++];
}
