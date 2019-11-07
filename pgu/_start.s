
# 使用 objdump -S 查看生成的object文件，
# 观察 _strart 和 $_start 的区别

.section .text
.globl _start

_start:

    movl _start, %ebx
    # movl $_start, %ebx
    movl $1, %eax
    int $0x80
