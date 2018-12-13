#include <stdio.h>
#include <time.h>

int main(void)
{
	char *wday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

	time_t timer;
	time(&timer); // 获取当前时间; 等同于 timer = time(NULL);

    struct tm *p;
    // gmtime 将 time_t 类型 转换为 tm 类型, 并设置时区为 greenwich mean time，即 UTC + 0 时区
    // localtime 将 time_t 类型 转换为 tm 类型, 并设置时区为本地时区
    // asctime 将 tm 结构体转换为 字符串

    p = gmtime(&timer);
	printf("UTC time: %s", asctime(p));

	p = localtime(&timer);
	printf("localtime: %s", asctime(p));

	printf("localtime: %d-%02d-%02d %02d:%02d:%02d\n",
            (1900+p->tm_year), (1+p->tm_mon), p->tm_mday,
            p->tm_hour, p->tm_min, p->tm_sec);

	printf("localtime: %s %d:%d:%d\n", wday[p->tm_wday],
            p->tm_hour, p->tm_min, p->tm_sec);
	return 0;
}
