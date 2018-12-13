#include <stdio.h>

//包含两个指向有13个元素的数组的指针的数组
int (*daytab[2])[13];

//从月/日转换为一年的第几天
int day_of_year(int year, int month, int day)
{
	if (year <= 0 || month < 1 || month > 12 || day < 1)
		return -1;

	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	if (day > (*daytab[leap])[month])
		return -1;

	for (i = 1; i < month; i++)
		day += (*daytab[leap])[i];
	return day;
}

//将一年的第几天转换为月/日
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	if (year < 1752) {
		return -1;
	}

	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if ( (leap && yearday > 366) || (!leap && yearday > 365))
		return -1;

	for (i = 1; yearday > (*daytab[leap])[i]; i++)
		yearday -= (*daytab[leap])[i];
	*pmonth = i;
	*pday = yearday;
	return 0;
}

//如果要将一个二维数组传递给函数，函数的参数声明中必须包括数组的列数
//更一般地，只有数组的第一个维度（下标）是可以不指定的，
//而其他维度都必须指定
//例如：func(int daytab[][13]) { … } 
int main()
{
	int commonyear[] ={ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	//平年 
	int leapyear[] ={ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	//闰年 
	daytab[0] = &commonyear;	//平年
	daytab[1] = &leapyear;	//闰年

	int y, m, d;
	y = 2017;
	m = 12;
	d = 5;
	int yearday = day_of_year(y, m, d);
	if (yearday > 0) {
		printf("day_of_year(%d, %d, %d) = %d.\n", y, m, d, yearday);

		if (month_day(y, yearday, &m, &d) == 0) {
			printf("the %d year's %dth day is %d-%d-%d.\n", y, yearday, y, m, d);
		} else {
			printf("error\n");
			return 1;
		}
	} else {
		printf("error\n");
		return 1;
	}

	
	return 0;
}

