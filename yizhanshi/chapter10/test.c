#include <stdio.h>

int add_range(int low, int high)
{
	int i, sum;
	for (i = low; i <= high; i++)
		sum = sum + i;
	return sum;
}

int fa(int x)
{
    int a = 10;
    int b = 13;
    printf("fa %p, a=%p, b=%p\n", &x, &a, &b);
    x += x;
    x += a + b;
    return x;
}

int fb(int x)
{
    printf("fb %p\n", &x);
    x = fa(x);
    x *= x;
    return x;
}

int fc(int x)
{
    printf("fc %p\n", &x);
    x *= 2;
    return x;
}

void foo(void)
{
    int i;
    printf("i = %d\n", i);
    i = 444;
}

int main(void)
{
	int result[100]= {};
	result[0] = add_range(1, 10);
	result[1] = add_range(1, 100);
	printf("result[0] = %d\nresult[1] = %d\n", result[0], result[1]);

    fa(1);
    fb(2);
    fa(3);
    fc(4);

    foo();
    printf("hello\n");
    foo();
	return 0;
}
