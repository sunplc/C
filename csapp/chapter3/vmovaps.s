	.file	"vmovaps.c"
	.text
	.globl	float_mov
	.type	float_mov, @function
float_mov:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	vmovss	%xmm0, -20(%rbp)
	movq	%rdi, -32(%rbp)
	movq	%rsi, -40(%rbp)
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movq	-40(%rbp), %rdx
	movl	-20(%rbp), %eax
	movl	%eax, (%rdx)
	movl	-4(%rbp), %eax
	movl	%eax, -24(%rbp)
	vmovss	-24(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	float_mov, .-float_mov
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
