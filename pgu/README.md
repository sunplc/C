
## Programming from ground up 64位版 示例和练习答案

- x86指令后缀意义：byte (8 bits), word (16bits), long (32bits), quadword (64bits), double quedword (128bits)

- 使用 uname -m 查看系统架构是32位或64位

- 64位系统的系统调用表的各个编号与32位的系统调用表的编号是不同的，可以查看 ABI 表了解详情

- 64位系统的函数调用惯例是使用寄存器保存参数，而不是像32位那样在函数调用前将参数压入栈中

- 64位系统中用户级函数调用分别使用下列寄存器存放参数: %rdi, %rsi, %rdx, %rcx, %r8 and %r9，内核接口使用 %rdi, %rsi, %rdx, %r10, %r8 和 %r9 存放参数

- 64位系统中函数返回值存放在 %rax 中

- 64位系统中系统调用编号存放在 %rax 中

- 64位系统中程序退出码存放在 %rdi 中

