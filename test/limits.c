#include <stdio.h>
#include <limits.h>	//整数最大值最小值限制		/usr/include/limits.h
#include <float.h>	//浮点数最大值最小值限制	/usr/lib/gcc/x86_64-linux-gnu/5/include/float.h

// 练习 2-1. 编写一个程序来确定 char、 short、 int 和 long 型变量的取值范围，
// 包括 signed 及 unsigned类型。通过打印标准头文件中的相应值以及直接计算两种方法来完成。
// 如果通过计算方式，确定各种浮点类型的取值范围会更困难。
int main()
{
	//打印标准头文件中的相应值
	// char
	printf("CHAR_MIN = %d\n", CHAR_MIN);
	printf("sizeof(CHAR_MAX) = %ld\n", sizeof(CHAR_MAX));
	printf("CHAR_MAX = %d\n", CHAR_MAX);	

	printf("UCHAR_MAX = %d\n\n", UCHAR_MAX);
	// short 
	printf("SHRT_MIN = %d\n", SHRT_MIN);
	printf("SHRT_MAX = %d\n", SHRT_MAX);
	printf("USHRT_MAX = %d\n\n", USHRT_MAX);
	// int
	printf("INT_MIN = %d\n", INT_MIN);
	printf("INT_MAX = %d\n", INT_MAX);
	printf("UINT_MAX = %u\n\n", UINT_MAX);
	// long
	printf("LONG_MIN = %ld\n", LONG_MIN);
	printf("sizeof(LONG_MAX) = %ld\n", sizeof(LONG_MAX));
	printf("LONG_MAX = %ld\n", LONG_MAX);
	printf("ULONG_MAX = %lu\n\n", ULONG_MAX);

	// long long
	printf("LLONG_MIN = %lld\n", LLONG_MIN);
	printf("LLONG_MAX = %lld\n", LLONG_MAX);
	printf("ULLONG_MAX = %llu\n\n", ULLONG_MAX);
	// float
	printf("FLT_MIN = %f\n", FLT_MIN);
	printf("FLT_MAX = %f\n\n", FLT_MAX);

	// double
	printf("DBL_MIN = %f\n", DBL_MIN);
	printf("sizeof(DBL_MAX) = %ld\n", sizeof(DBL_MAX));
	printf("DBL_MAX = %f\n\n", DBL_MAX);

	unsigned short s = ~0;
	printf("max unsigned short = %u\n", s);
	s >>= 1;
	printf("max short = %d\n", s);
	printf("min short = %d\n\n", -s-1);

	unsigned int i = ~0;
	printf("max unsigned int = %u\n", i);
	i >>= 1;
	printf("max int = %d\n", i);
	printf("min int = %d\n\n", -i-1);

    printf("最大文件名：%d\n", NAME_MAX);
    printf("最大路径名：%d\n\n", PATH_MAX);

	return 0;
}

