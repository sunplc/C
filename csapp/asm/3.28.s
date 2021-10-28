	.file	"3.28.c"
	.section	.rodata
.LC0:
	.string	"input an intger:"
.LC1:
	.string	"%d"
.LC2:
	.string	"%d\n"
.LC3:
	.string	"switch:"
.LC4:
	.string	"1"
.LC5:
	.string	"5"
.LC6:
	.string	"100"
.LC7:
	.string	"1000"
.LC8:
	.string	"default"
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
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$.LC0, %edi
	call	puts
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC3, %edi
	call	puts
	movl	-4(%rbp), %eax
	cmpl	$5, %eax
	je	.L3
	cmpl	$5, %eax
	jg	.L4
	cmpl	$1, %eax
	je	.L5
	jmp	.L2
.L4:
	cmpl	$100, %eax
	je	.L6
	cmpl	$1000, %eax
	je	.L7
	jmp	.L2
.L5:
	movl	$.LC4, %edi
	call	puts
	jmp	.L9
.L3:
	movl	$.LC5, %edi
	call	puts
	jmp	.L9
.L6:
	movl	$.LC6, %edi
	call	puts
	jmp	.L9
.L7:
	movl	$.LC7, %edi
	call	puts
	jmp	.L9
.L2:
	movl	$.LC8, %edi
	call	puts
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
