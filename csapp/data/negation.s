	.file	"negation.c"
	.section	.rodata
.LC0:
	.string	"0x"
.LC1:
	.string	"%.2x"
	.text
	.globl	show_bytes
	.type	show_bytes, @function
show_bytes:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	cltq
	subq	$1, %rax
	addq	%rax, -8(%rbp)
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	leaq	-1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L2:
	movl	-12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -12(%rbp)
	testl	%eax, %eax
	jg	.L3
	movl	$10, %edi
	call	putchar
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	show_bytes, .-show_bytes
	.section	.rodata
.LC2:
	.string	"x = %d, y = %d, x + y = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$-2147483648, -4(%rbp)
	movl	-4(%rbp), %eax
	negl	%eax
	movl	%eax, -8(%rbp)
	leaq	-4(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	show_bytes
	leaq	-8(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	show_bytes
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$-12345, -4(%rbp)
	movl	-4(%rbp), %eax
	negl	%eax
	movl	%eax, -8(%rbp)
	leaq	-4(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	show_bytes
	leaq	-8(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	show_bytes
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
