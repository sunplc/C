/*
 * 浮点数的存储方式, 从高位到低位：
 * 符号位 -> 指数 -> 小数, 权重越来越小;
 * 所以除符号位相反外，浮点数可以直接当作无符号整数来比较大小
 * 
 * 如果是负数，将其指数位和小数位取反；
 * 因为负数越大，其绝对值越小，取反后作为整数来看，其值越大
 * 然后就可以将浮点数看作无符号整数直接比较大小
 */
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, int len) {
    p = p + len - 1;
    printf("0x ");
    while (len-- > 0) {
        printf("%.2X ", *p--);
    }
    printf("\n");
}

unsigned f2u(float x)
{
    float *fp = &x;
    return * (unsigned *)fp;
}

int float_le(float x, float y)
{
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    //unsigned u = (ux ^ (~(sx-1)));
    //show_bytes((byte_pointer) &ux, sizeof(unsigned));
    //show_bytes((byte_pointer) &u, sizeof(unsigned));

    //u = (uy ^ (~(sy-1)));
    //show_bytes((byte_pointer) &uy, sizeof(unsigned));
    //show_bytes((byte_pointer) &u, sizeof(unsigned));

    // 方法一：
    // 先根据符号位比较大小，如果是负数再将指数位和小数位取反，
    // 然后作为无符号整数比较大小
    // return (sx > sy) || (!(sx < sy) && ((ux ^ (~(sx-1))) <= (uy ^ (~(sy-1)))) );

    // 方法二：
    // 将符号位先取反，如果是负数再将指数位和小数位取反，
    // 然后作为无符号整数比较大小
    return ((ux ^ (1<<31)) ^ (~(sx-1))) <= ((uy ^ (1<<31)) ^ (~(sy-1)));
}

int main(int argc, char* argv[])
{
    float f = -1231432;
    float f2 = -123;
    printf("float_le(%f, %f) = %d\n", f, f2, float_le(f, f2));

    return 0;
}

