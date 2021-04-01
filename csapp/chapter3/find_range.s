	.file	"find_range.c"
	.text
	.globl	find_range
	.type	find_range, @function
find_range:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	vmovss	%xmm0, -4(%rbp)
	vxorps	%xmm0, %xmm0, %xmm0
	vucomiss	-4(%rbp), %xmm0
	jbe	.L12
	movl	$0, %eax
	jmp	.L4
.L12:
	vxorps	%xmm0, %xmm0, %xmm0
	vucomiss	-4(%rbp), %xmm0
	jp	.L5
	vxorps	%xmm0, %xmm0, %xmm0
	vucomiss	-4(%rbp), %xmm0
	jne	.L5
	movl	$1, %eax
	jmp	.L4
.L5:
	vmovss	-4(%rbp), %xmm0
	vxorps	%xmm1, %xmm1, %xmm1
	vucomiss	%xmm1, %xmm0
	jbe	.L13
	movl	$2, %eax
	jmp	.L4
.L13:
	movl	$3, %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	find_range, .-find_range
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
