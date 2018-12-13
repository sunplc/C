#include <stdio.h>

int main(void)
{
	char amessage[] = "now is the time";	//数组
	char *pmessage = "now is the time";		//指针

	printf("amessage = %s\n", amessage);
	printf("pmessage = %s\n", pmessage);

	printf("pmessage = %p\n", pmessage);
	//将另一个字符串常量"hello"的地址赋值给指针pmessage
	pmessage = "hello";	
	printf("pmessage = %p\n", pmessage);

	printf("*pmessage = %c\n", *pmessage);
	pmessage++;
	printf("*pmessage = %c\n", *pmessage);

	//在c语言编译时，字符串常量是存储在数据段中的，是不能修改的，
	//通过指针修改数据段中的内容，会报 segment fault
	//数据段位于内存中的低地址，类似：0x4006e8
	//*pmessage = 97;

	printf("pmessage = %s\n", pmessage);
	return 0;
}

