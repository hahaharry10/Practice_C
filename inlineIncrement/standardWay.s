	.text
	.file	"standardWay.c"
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	str	wzr, [sp, #44]
	str	wzr, [sp, #40]
	b	.LBB0_1
.LBB0_1:                                // =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #40]
	subs	w8, w8, #10
	cset	w8, ge
	tbnz	w8, #0, .LBB0_3
	b	.LBB0_2
.LBB0_2:                                //   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #40]
	ldrsw	x10, [sp, #40]
	mov	x9, sp
	str	w8, [x9, x10, lsl #2]
	ldr	w8, [sp, #40]
	add	w8, w8, #1
	str	w8, [sp, #40]
	b	.LBB0_1
.LBB0_3:
	mov	w0, wzr
	add	sp, sp, #48
	.cfi_def_cfa_offset 0
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        // -- End function
	.ident	"Debian clang version 16.0.6 (27+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
