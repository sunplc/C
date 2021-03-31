	.file	"test.c"
	.section	.rodata
.LC1:
	.string	"%df\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	.LC0(%rip), %eax
	movl	%eax, -4(%rbp)
	vmovss	-4(%rbp), %xmm1
	vcvtps2pd	%xmm1, %xmm1
	vmovsd	%xmm1, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	vmovsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1094842424
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
