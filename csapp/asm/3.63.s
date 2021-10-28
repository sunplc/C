	.file	"3.63.c"
	.text
	.globl	switch_prob_goto
	.type	switch_prob_goto, @function
switch_prob_goto:
.LFB0:
	.cfi_startproc
	subq	$60, %rsi
	cmpq	$5, %rsi
	jg	.L2
	jmp	*jt.1727(,%rsi,8)
.L3:
	leaq	0(,%rdi,8), %rax
	ret
.L5:
	movq	%rdi, %rax
	sarq	$3, %rax
	ret
.L6:
	movq	%rdi, %rax
	salq	$4, %rax
	subq	%rdi, %rax
	movq	%rax, %rdi
.L7:
	imulq	%rdi, %rdi
.L2:
	leaq	75(%rdi), %rax
.L4:
	ret
	.cfi_endproc
.LFE0:
	.size	switch_prob_goto, .-switch_prob_goto
	.globl	switch_prob
	.type	switch_prob, @function
switch_prob:
.LFB1:
	.cfi_startproc
	subq	$60, %rsi
	cmpq	$5, %rsi
	ja	.L9
	jmp	*.L11(,%rsi,8)
	.section	.rodata
	.align 8
	.align 4
.L11:
	.quad	.L10
	.quad	.L9
	.quad	.L10
	.quad	.L12
	.quad	.L13
	.quad	.L14
	.text
.L10:
	leaq	0(,%rdi,8), %rax
	ret
.L12:
	movq	%rdi, %rax
	sarq	$3, %rax
	ret
.L13:
	movq	%rdi, %rax
	salq	$4, %rax
	subq	%rdi, %rax
	movq	%rax, %rdi
.L14:
	imulq	%rdi, %rdi
.L9:
	leaq	75(%rdi), %rax
	ret
	.cfi_endproc
.LFE1:
	.size	switch_prob, .-switch_prob
	.section	.rodata
	.align 32
	.type	jt.1727, @object
	.size	jt.1727, 48
jt.1727:
	.quad	.L3
	.quad	.L2
	.quad	.L3
	.quad	.L5
	.quad	.L6
	.quad	.L7
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
