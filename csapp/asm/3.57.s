	.file	"3.57.c"
	.text
	.globl	funct3
	.type	funct3, @function
funct3:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	vmovsd	%xmm0, -32(%rbp)
	movq	%rsi, -40(%rbp)
	movq	%rdx, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	vcvtsi2sd	%eax, %xmm0, %xmm0
	vmovsd	%xmm0, -16(%rbp)
	vmovsd	-32(%rbp), %xmm0
	vucomisd	-16(%rbp), %xmm0
	jbe	.L6
	vcvtsi2ssq	-40(%rbp), %xmm0, %xmm0
	vmovss	-4(%rbp), %xmm1
	vmulss	%xmm0, %xmm1, %xmm0
	vmovss	%xmm0, -4(%rbp)
	vmovss	-4(%rbp), %xmm0
	vcvtps2pd	%xmm0, %xmm0
	jmp	.L4
.L6:
	vmovss	-4(%rbp), %xmm0
	vaddss	%xmm0, %xmm0, %xmm0
	vmovss	%xmm0, -4(%rbp)
	vcvtsi2ssq	-40(%rbp), %xmm0, %xmm0
	vaddss	-4(%rbp), %xmm0, %xmm0
	vunpcklps	%xmm0, %xmm0, %xmm0
	vcvtps2pd	%xmm0, %xmm0
.L4:
	vmovsd	%xmm0, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -56(%rbp)
	vmovsd	-56(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	funct3, .-funct3
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
