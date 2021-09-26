	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_sum                            ; -- Begin function sum
	.p2align	2
_sum:                                   ; @sum
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32                     ; =32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #24]
	str	w1, [sp, #20]
	str	wzr, [sp, #12]
	str	wzr, [sp, #16]
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #20]
	subs	w8, w8, w9
	b.ge	LBB0_4
; %bb.2:                                ;   in Loop: Header=BB0_1 Depth=1
	ldr	x8, [sp, #24]
	ldrsw	x9, [sp, #16]
	ldr	w9, [x8, x9, lsl #2]
	ldr	w8, [sp, #12]
	add	w8, w8, w9
	str	w8, [sp, #12]
; %bb.3:                                ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #16]
	add	w8, w8, #1                      ; =1
	str	w8, [sp, #16]
	b	LBB0_1
LBB0_4:
	ldr	w0, [sp, #12]
	add	sp, sp, #32                     ; =32
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
