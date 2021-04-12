/*
setx 指令的操作数只能为一个字节长度的寄存器或内存块
setx 指令在不符合条件时将操作数设置为0；
符合条件时将操作数设置为1。

验证 setx 系列指令只会修改寄存器的最低位的一个字节，
不会修改高字节的值，
例如：setg %al, 只会将 %eax 寄存器
的最低字节设置为1，其它高字节的位不变。

将 %eax 设置为 -1，二进制表示：
11111111 11111111 11111111 11111111 
setg 将 %al 设置为1之后，%eax的二进制表示为：
11111111 11111111 11111111 00000001 
即 -255。本程序输出结果也为-255，表示验证正确

*/

.section .data

output_int:
    .ascii "int: %d\n\0"

.section .text
.globl _start
_start:

    movl $0, %ecx

    movl $1, %eax
    movl $2, %ebx
    subl %eax, %ebx

    setg %cl
 
    movq $output_int, %rdi
    movslq %ecx, %rsi # 把d的值放入寄存器
    mov $2, %al
    call printf

    # Exit this program
    movq $0, %rdi
    call exit

