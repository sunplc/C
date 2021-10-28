	.file	"4.47.c"
	.text
	.p2align 4,,15
	.globl	bubble_a
	.type	bubble_a, @function
bubble_a:
.LFB11:
	.cfi_startproc
	subq	$1, %rsi
	testq	%rsi, %rsi
	jle	.L13
	.p2align 4,,10
	.p2align 3
.L10:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L7:
	movq	8(%rdi,%rax,8), %rdx
	movq	(%rdi,%rax,8), %rcx
	cmpq	%rcx, %rdx
	jge	.L3
	movq	%rcx, 8(%rdi,%rax,8)
	movq	%rdx, (%rdi,%rax,8)
.L3:
	addq	$1, %rax
	cmpq	%rsi, %rax
	jl	.L7
	subq	$1, %rsi
	jne	.L10
	rep ret
.L13:
	.p2align 4,,7
	rep ret
	.cfi_endproc
.LFE11:
	.size	bubble_a, .-bubble_a
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld "
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$8, %esi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$72, %rsp
	.cfi_def_cfa_offset 96
	leaq	64(%rsp), %rbp
	movq	%rsp, %rdi
	movq	%rsp, %rbx
	movq	$32, (%rsp)
	movq	$12, 8(%rsp)
	movq	$4345, 16(%rsp)
	movq	$5, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$-344, 40(%rsp)
	movq	$-2, 48(%rsp)
	movq	$453, 56(%rsp)
	call	bubble_a
	.p2align 4,,10
	.p2align 3
.L16:
	movq	(%rbx), %rsi
	xorl	%eax, %eax
	movl	$.LC0, %edi
	addq	$8, %rbx
	call	printf
	cmpq	%rbp, %rbx
	jne	.L16
	addq	$72, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
