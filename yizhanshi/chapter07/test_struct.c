#include <stdio.h>

struct coordinate {
	double x, y;
};

struct complex_struct {
	double x, y;	
};

void print_struct_rhombus(struct complex_struct z)
{
	if (z.y < 0)
		printf("z=%f%fi\n", z.x, z.y);	
	else 
		printf("z=%f+%fi\n", z.x, z.y);
}

struct complex_struct add_rhombus(struct complex_struct z1, struct complex_struct z2)
{
	z1.x = z1.x + z2.x;
	z1.y = z1.y + z2.y;
	return z1;
}

int main(void)
{
	double x = 3.0;
	//struct complex_struct z;
	//z = {x, 4.0};
	struct complex_struct z;
	z = (struct complex_struct){3.4, x};
	//z.x = x;
	//z.y = 4.0;
	struct complex_struct z1 = { .y = 5.0,  .x = 6.0}, z2 = {.y = 7.0};
	//z1.x = 4.0;
	z1 = z2;
	//z2.y = 3.0;
	struct complex_struct z3 = add_rhombus(z1, z2);
	print_struct_rhombus(z);
	print_struct_rhombus(z1);
	print_struct_rhombus(z3);
	return 0;
}
