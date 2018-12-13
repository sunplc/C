#include <stdio.h> 

int main()
{
	void print_num(int);
	int a = 123;
	print_num(a);
	return 0; 
}

void print_num(int a)
{
	printf("十位是 %d\n", (a % 100 - a % 10) / 10);	
	printf("个位是 %d\n", a % 10);
}
