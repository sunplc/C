
rsum:
	#movl	$0, %eax
    irmovq $0, %rax
	andq	%rsi, %rsi
	jle	.test
	pushq	%rbx
	rrmovq	%rdi, %rbx
    irmovq  $1, %r8
	subq	%r8, %rsi

	#leaq	8(%rdi), %rdi
    irmovq  $8, %r9
    addq    %r9, %rdi

	call	rsum
    # addq  (%rbx), %rax
    mrmovq  (%rbx), %r10
	addq	%r10, %rax
	popq	%rbx
.test:
	rep ret
