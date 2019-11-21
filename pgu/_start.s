# 32位版本，可以在 x86_64 上正常执行

.section .text
.globl _start

_start:

    # 使用 objdump -S 分别查看生成的object文件，
    # 观察其中 _start 和 $_start 的区别
    movl _start, %ebx
    # movl $_start, %ebx

    movl $1, %eax
    int $0x80
