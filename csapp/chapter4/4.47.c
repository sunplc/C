#include <stdio.h>


void bubble_a(long *data, long count)
{
    long i, last;
    for (last = count-1; last > 0; last--) {
        for (i = 0; i < last; i++) 
            if (*(data+i+1) < *(data+i)) {
                long t = *(data+i+1);
                *(data+i+1) = *(data+i);
                *(data+i) = t;
            }
    }
}

int main()
{
    long arr[] = {32,12,4345,5,0,-344,-2,453};
    long len = sizeof(arr)/sizeof(long);

    bubble_a(arr, len);

    long i;
    for (i = 0; i < len; i++) {
        printf("%ld ", arr[i]);
    }
}
