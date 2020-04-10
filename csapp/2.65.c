#include <stdio.h>

/* Return 1 when x contains an odd number of 1s;
 * 0 otherwise. Assume w=32. 
 *
 * 返回 1 如果 x 含有奇数个1，否则返回0；
 * 假设 int 类型的长度是32位
 */
int odd_ones(unsigned x) {

    // 将x的高位的一半和低位的一半进行异或操作,
    // 如果相比较的两个位同为1则相抵消为0，
    // 只有一个位是1则会保留在x的低位的一半的位中;
    // 完成这一异或操作后，再将x的低位的一半分为两半，
    // 将这两半再进行异或操作，重复这个对半异或的操作；
    // 最终只剩下最低的一位，最低的一位是1就表示抵消了
    // 若干对1之后还有一个1，就是说共有奇数个1，否则就是
    // 偶数个1。

    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;

    return x & 1;
}

int main(int argc, char* argv[])
{
    int x = 0b01000000110000000000000000010001;
    printf("odd_ones(x) = %d\n", odd_ones(x));

    return 0;
}

