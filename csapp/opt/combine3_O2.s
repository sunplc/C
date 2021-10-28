	.file	"combine3.c"
	.text
	.p2align 4,,15
	.globl	combine1
	.type	combine1, @function
combine1:
.LFB11:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rsi, %rbx
	call	vec_length
	movl	$0, (%rbx)
	movq	%rax, %r12
	movq	%rbp, %rdi
	call	get_vec_start
	testq	%r12, %r12
	jle	.L1
	movq	%rax, %rdx
	movl	(%rbx), %eax
	leaq	(%rdx,%r12,4), %rcx
	.p2align 4,,10
	.p2align 3
.L4:
	addl	(%rdx), %eax
	addq	$4, %rdx
	cmpq	%rcx, %rdx
	movl	%eax, (%rbx)
	jne	.L4
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	combine1, .-combine1
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"*dest = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$12000000, %edi
	call	new_vec
	leaq	12(%rsp), %rsi
	movq	%rax, %rdi
	call	combine1
	movl	12(%rsp), %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
