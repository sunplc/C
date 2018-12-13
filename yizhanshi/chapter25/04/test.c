/* malloc calloc realloc 都是在堆空间分配内存 alloca是在栈空间上分配内存，属于POSIX标准 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	typedef struct {
		int a;
		char str[4];
		//char str[10];
	} unit;
	printf("sizeof unit is %ld\n", sizeof(unit));

	unit *ptr;

	/* void *calloc(size_t nmemb, size_t size);
	   calloc 分配内存后会将分配的内存空间用字节0填充, c 可以理解为clear
	   而malloc并不负责把分配的内存空间清零 */
	ptr = calloc(2, sizeof(unit));

	char *tmp_ptr = ptr;
	int i;
	for (i = 0; i < 32; i++) {
		printf("%p\n", tmp_ptr);
		printf("%d\n", *tmp_ptr);	
		++tmp_ptr;
	}

	/* void *realloc(void *ptr, size_t size);
	   用malloc或calloc分配的内存使用了一段时间后需要改变它的大小，
	   一种方法是调用malloc分配一块新的内存空间，把原内存空间中的数据拷贝到新的内存空间，然后调用free释放原内存空间。
	   使用realloc函数简化了这些步骤，通过参数ptr把原内存空间的指针传给realloc，通过参数size设定新的空间大小（字节数），
	   realloc返回新的内存空间的首地址，并释放原空间地址 */	
	char *reptr = realloc(ptr, sizeof(unit) *3);
	printf("new memory pointer is %p\n", reptr);
	return 0;
}

