#include <stdio.h>

int main()
{
	int arr[3] = {17, 3, 7};

	printf("%p\n", arr);
	printf("%p\n", &arr);
	// 以上两行输出的结果相同
	
	// 指向数组的指针，可以当作数组来使用，实现数组的相同功能
	int *x = arr;
	int i;
	for (i = 0; i < 3; ++i) 
		printf("x[%d] = %d\n", i, x[i]);

	// 数组也可以被当作指针来进行取值操作，但是数组不是左值，不能直接对其进行修改
	printf("*arr = %d\n", *arr);
	// arr++; printf("*arr = %d\n", *arr); //错误
	
	// 数组就是编译器实现的，由多个连续的固定单位的字节块构成的内存块，其中存储着每个元素的值，
	// 不同之处在于，指针变量有自己的内存空间，其中存放着一个内存地址，而数组没有
	// 因此： int *p = arr; 和 int *p = &arr; 是等价的
	
	
	// int **pp = &arr; printf("**pp = %d\n", **pp); // 是错误的  Segmentation fault (core dumped)
	int *p = arr; int **pp = &p; printf("**pp = %d\n", **pp); // 是正确的

    puts("-----------------------------------");

	int array[5] = {3,4,5,6,7};
	printf("%p %ld\n", array, sizeof(array));
	printf("%p %ld\n", &array[0], sizeof(array[0]));
	printf("%p %ld\n\n", &array, sizeof(&array));

	printf("%p\n", array + 1);
	printf("%p\n", &array[0] + 1);
	// &array 是数组类型的指针，加一会使其指向的地址向后移动array大小(本例中是5*4=20个字节)个单位
	printf("%p\n", &array + 1); 

	return 0;
}
