#include <stdio.h>
#include <string.h>
#include <sys/time.h>

/* Basic implementation of memset */
void *basic_memset(void *s, int c, size_t n)
{
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    return s;
}

void *memset_word_level(void *s, int c, size_t n)
{
    unsigned char *schar = s;

    unsigned long w = 0;
    size_t wlen = sizeof(w); // word length in bytes

    size_t mod, cnt;
    size_t hlen, wcnt, tlen; // head char write length, word level write times, tail char write length

    if (n >= wlen) {
        mod = (size_t)schar % wlen;
        if (mod == 0) {
            hlen = 0;
            wcnt = n / wlen;
            tlen = n % wlen;
        } else {
            hlen = wlen - mod;
            tlen = (size_t)(schar + n) % wlen;
            wcnt = (n - hlen - tlen) / wlen;
        }
    } else {
        hlen = n;
        tlen = wcnt = 0;
    }

    //printf("%lu, %lu, %lu\n", hlen, wcnt, tlen);

    for (cnt = 0; cnt < hlen; cnt++) {
        *schar++ = (unsigned char) c;
    }

    if (wcnt > 0) {
        unsigned long *slong = (unsigned long *)schar;

        for (cnt = 0; cnt < wlen; cnt++) {
            w = (w << 8) | c;
        }
        //printf("wlen=%ld, w=%ld\n", wlen, w);

        // loop unrolling, tried 2 *2, 4 * 4, 8 * 8
        size_t unroll_size = 8;

        int limit = (int) (wcnt - unroll_size);
        cnt = 0;
        for (; cnt < limit; cnt += unroll_size) {
            *slong = w;
            *(slong+1) = w;
            *(slong+2) = w;
            *(slong+3) = w;
            *(slong+4) = w;
            *(slong+5) = w;
            *(slong+6) = w;
            *(slong+7) = w;
            *slong += unroll_size;
        }

        while (cnt < wcnt) {
            *slong++ = w;
            cnt++;
        }

        schar = (unsigned char *)slong;
    }

    for (cnt = 0; cnt < tlen; cnt++) {
        *schar++ = (unsigned char) c;
    }
    
    return s;
}


int main(int argc, char *argv[])
{
    size_t i, len = 5000000;
    char str[len];
    for (i = 0; i < len; i++) {
        str[i] = 0;
    }

    struct timeval start;
    struct timeval end;
    float timer;

    gettimeofday(&start,NULL); //结构体start当前时间（1970年1月1日到现在的时间）
    basic_memset(str, 69, len-1);
    gettimeofday(&end,NULL);
    //计算start和end之间的时间差
    timer = end.tv_sec - start.tv_sec + (float)(end.tv_usec - start.tv_usec)/1000000;    
    printf("basic_memset time:\n %fs\n",timer);

    gettimeofday(&start,NULL); //结构体start当前时间（1970年1月1日到现在的时间）
    memset_word_level(str, 69, len-1);
    gettimeofday(&end,NULL);
    //计算start和end之间的时间差
    timer = end.tv_sec - start.tv_sec + (float)(end.tv_usec - start.tv_usec)/1000000;    
    printf("memset_word_level time:\n %fs\n",timer);

    //printf("%s<<<", str);
    return 0;
}
