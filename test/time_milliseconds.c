#include <stdio.h>
#include <sys/time.h>

void print_millisecond (void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);

    double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
    printf("%f\n", time_in_mill);
}

long long current_timestamp() {

    struct timeval te; 

    gettimeofday(&te, NULL); // get current time

    printf("Seconds: %lld \nNanoseconds: %ld\n", (long long)te.tv_sec, (long)te.tv_usec);

    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    printf("milliseconds: %lld\n", milliseconds);

    return milliseconds;
}

int main()
{
    current_timestamp();
    //print_millisecond();
    return 0;
}

