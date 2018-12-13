#include <stdio.h>
#include <math.h>

// RECTANGULAR	直角坐标 
// POLAR		极坐标
enum coordinate_type { RECTANGULAR, POLAR };
// 指定向量的坐标类型
struct complex_struct {
	enum coordinate_type t;
	double a, b;
};

struct complex_struct make_from_real_img(double x, double y)
{
	struct complex_struct z;
	z.t = RECTANGULAR;
	z.a = x;
	z.b = y;
	return z;
}

struct complex_struct make_from_mag_ang(double r, double A)
{
	struct complex_struct z;
	z.t = POLAR;
	z.a = r;
	z.b = A;
	return z;
}

int type_mark(struct complex_struct z)
{
	return z.t;
}

double real_part(struct complex_struct z)
{
	if (z.t == RECTANGULAR)
		return z.a;
	else
		return z.a * cos(z.b);
}

double img_part(struct complex_struct z)
{
	if (z.t == RECTANGULAR)
		return z.b;
	else
		return z.a * sin(z.b);
} 

double magnitude(struct complex_struct z)
{
	if (z.t == POLAR)
		return z.a;
	else
		return sqrt(z.a * z.a + z.b * z.b);
}

double angle(struct complex_struct z)
{
	if (z.t == POLAR)
		return z.b;
	else
		return atan2(z.b, z.a);
}

int main(void)
{
	struct complex_struct z1 = make_from_real_img(3, 4);
	struct complex_struct z2 = make_from_mag_ang(5, 0.927295); 
	printf("t = %d, a = %f, b = %f, a = %f, b = %f\n", type_mark(z1),
			real_part(z1), img_part(z1), magnitude(z1), angle(z1));
	printf("t = %d, a = %f, b = %f, a = %f, b = %f\n", type_mark(z2),
			real_part(z2), img_part(z2), magnitude(z2), angle(z2));
	return 0;
}
