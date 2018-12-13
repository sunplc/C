#include <stdio.h>
#include <unistd.h> // unlink()

int main(int argc, char *argv[])
{
	//删除一个文件
	int result  = unlink("1.txt");
	printf("result = %d\n", result);
	return 0;
}

