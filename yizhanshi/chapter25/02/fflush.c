/*行缓冲：写入的数据中有换行符或者缓冲区写满，才会写入内核
 ,标准输入和标准输出对应的设备通常是行缓冲的
 */
#include <stdio.h>

int main(void)
{
	printf("hello world");
	fflush(stdout);//将文件缓冲区的内容通过内核立即写入到文件或设备
	while(1);
	return 0;
}

