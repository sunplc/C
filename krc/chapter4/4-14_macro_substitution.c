#include <stdio.h>

#define arr_len(arr) (int)(sizeof(arr) / sizeof(arr[0]))
#define forever for(;;)
#define max(x, y) ((x) > (y) ? (x) : (y))
#define square(x) (x) * (x)
#define dprint(expr) printf(#expr " = %g\n", expr)
//#define swap(t, x, y) t temp = (x); (x) = (y); (y) = temp
#define swap(t, x, y) {t temp = (x); (x) = (y); (y) = temp;} 

// 练习 4-14. 定义一个宏 swap(t, x, y)，
// 它将类型为 t 的两个参数 x、y彼此互换。
// （使用程序块结构会有所帮助。）
int main()
{
	int arr[] = {1, 2, 3, 4};
	printf("arr's length = %d\n", arr_len(arr));

	//forever putchar('x');

	int i = max(7, 3.14);
	printf("i = %d\n", i);

	int a = 13;
	a = square(a);
	printf("a = %d\n", a);

	dprint(3.2 + a);

	int x = 13, y = 14;
	swap(double , x, y);
	printf("x = %d, y = %d\n", x, y);
	

	return 0;
}

