/*
 * x at %ebp+8, y at %ebp+12
 *
 * 1 movl 8(%ebp), %ebx
 * 2 movl 12(%ebp), %ecx
 * 3 testl %ecx, %ecx
 * 4 jle .L2            # y > 0
 * 5 movl %ebx, %edx
 * 6 subl %ecx, %edx    # edx = x - y
 * 7 movl %ecx, %eax
 * 8 xorl %ebx, %eax    # eax = y ^ x
 * 9 cmpl %ecx, %ebx
 * 10 cmovl %edx, %eax  # eax = x - y < 0 ? edx : eax
 * 11 jmp .L4
 * 12 .L2:
 * 13 leal 0(,%ebx,4), %edx     # edx = x * 4
 * 14 leal (%ecx,%ebx), %eax    # eax = x + y
 * 15 cmpl $-2, %ecx
 * 16 cmovge %edx, %eax         # eax = y >= -2 ? edx : eax
 * 17 .L4:
 *                              # return eax
 */

int test(int x, int y) {
    int val = x + y;
    if (y > 0) {
        if (x < y)
            val = x - y;
        else
            val = y ^ x;
    } else if (y >= -2)
        val = x * 4;
    return val; 
}

