	.file	"3.60.c"
	.text
	.globl	loop
	.type	loop, @function
loop:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movb	%al, -17(%rbp)
	movsbq	-17(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	$0, -8(%rbp)
	movq	$1, -16(%rbp)
	jmp	.L2
.L3:
	movq	-16(%rbp), %rax
	movq	-40(%rbp), %rdx
	andq	%rdx, %rax
	orq	%rax, -8(%rbp)
	movq	-48(%rbp), %rax
	movl	%eax, %ecx
	salq	%cl, -16(%rbp)
.L2:
	cmpq	$0, -16(%rbp)
	jne	.L3
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	loop, .-loop
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
