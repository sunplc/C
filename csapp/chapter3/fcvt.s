	.file	"fcvt.c"
	.text
	.globl	fcvt
	.type	fcvt, @function
fcvt:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	vmovsd	-16(%rbp), %xmm0
	vcvttsd2siq	%xmm0, %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, (%rax)
	vcvtsi2ss	-36(%rbp), %xmm0, %xmm0
	movq	-48(%rbp), %rax
	vmovss	%xmm0, (%rax)
	vcvtsi2sdq	-24(%rbp), %xmm0, %xmm0
	movq	-56(%rbp), %rax
	vmovsd	%xmm0, (%rax)
	vmovss	-4(%rbp), %xmm0
	vcvtps2pd	%xmm0, %xmm0
	vmovsd	%xmm0, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -72(%rbp)
	vmovsd	-72(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	fcvt, .-fcvt
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
