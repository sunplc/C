.LC0:
	.string	"%ld "
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15


	.text
	.globl	bubble_a
	.type	bubble_a, @function
bubble_a:
	subq	$1, %rsi
	andq	%rsi, %rsi
	jle	.L13
.L10:
	xorl	%eax, %eax
.L7:
	mrmovq	8(%rdi,%rax,8), %r8
	mrmovq	(%rdi,%rax,8), %r9

    rrmovq %r8, %r10
    rrmovq %r9, %r11

    #对两个变量连续使用三次xor，可以用于交换两个变量的值
    # 这里我们在第一次xor后使用cmov来达到根据条件决定是否交换两个变量的值
    xorq %r8, %r9
	subq %r11, %r10
    cmovge %r11, %r8
    xorq %r9, %r8
    xorq %r8, %r9

	rmmovq	%r9, 8(%rdi,%rax,8)
	rmmovq	%r10, (%rdi,%rax,8)
.L3:
	addq	$1, %rax
	cmpq	%rsi, %rax
	jl	.L7
	subq	$1, %rsi
	jne	.L10
	rep ret
.L13:
	rep ret

	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	irmovl	$8, %esi
	pushq	%rbx
	subq	$72, %rsp
	leaq	64(%rsp), %rbp
	rrmovq	%rsp, %rdi
	rrmovq	%rsp, %rbx
	irmovq	$32, (%rsp)
	irmovq	$12, 8(%rsp)
	irmovq	$4345, 16(%rsp)
	irmovq	$5, 24(%rsp)
	irmovq	$0, 32(%rsp)
	irmovq	$-344, 40(%rsp)
	irmovq	$-2, 48(%rsp)
	irmovq	$453, 56(%rsp)
	call	bubble_a
.L16:
	mrmovq	(%rbx), %rsi
	xorl	%eax, %eax
	mrmovl	$.LC0, %edi
	addq	$8, %rbx
	call	printf
	cmpq	%rbp, %rbx
	jne	.L16
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	ret
