
standardWay:	file format elf64-littleaarch64

Sections:
Idx Name               Size     VMA              Type
  0                    00000000 0000000000000000 
  1 .interp            0000001b 0000000000000238 DATA
  2 .note.gnu.build-id 00000024 0000000000000254 
  3 .note.ABI-tag      00000020 0000000000000278 
  4 .gnu.hash          0000001c 0000000000000298 
  5 .dynsym            000000d8 00000000000002b8 
  6 .dynstr            0000008d 0000000000000390 
  7 .gnu.version       00000012 000000000000041e 
  8 .gnu.version_r     00000030 0000000000000430 
  9 .rela.dyn          000000c0 0000000000000460 
 10 .rela.plt          00000060 0000000000000520 
 11 .init              0000001c 0000000000000580 TEXT
 12 .plt               00000060 00000000000005a0 TEXT
 13 .text              00000178 0000000000000600 TEXT
 14 .fini              00000018 0000000000000778 TEXT
 15 .rodata            00000004 0000000000000790 DATA
 16 .eh_frame_hdr      0000003c 0000000000000794 DATA
 17 .eh_frame          000000c0 00000000000007d0 DATA
 18 .init_array        00000008 000000000001fdc8 
 19 .fini_array        00000008 000000000001fdd0 
 20 .dynamic           000001e0 000000000001fdd8 
 21 .got               00000030 000000000001ffb8 DATA
 22 .got.plt           00000038 000000000001ffe8 DATA
 23 .data              00000010 0000000000020020 DATA
 24 .bss               00000008 0000000000020030 BSS
 25 .comment           00000042 0000000000000000 
 26 .symtab            00000840 0000000000000000 
 27 .strtab            00000232 0000000000000000 
 28 .shstrtab          00000103 0000000000000000 

Disassembly of section .init:

0000000000000580 <_init>:
     580: d503233f     	paciasp
     584: a9bf7bfd     	stp	x29, x30, [sp, #-0x10]!
     588: 910003fd     	mov	x29, sp
     58c: 9400002a     	bl	0x634 <call_weak_fn>

0000000000000590 <$x>:
     590: a8c17bfd     	ldp	x29, x30, [sp], #0x10
     594: d50323bf     	autiasp
     598: d65f03c0     	ret

Disassembly of section .plt:

00000000000005a0 <$x>:
     5a0: a9bf7bf0     	stp	x16, x30, [sp, #-0x10]!
     5a4: f00000f0     	adrp	x16, 0x1f000 <__FRAME_END__+0x1e774>
     5a8: f947fe11     	ldr	x17, [x16, #0xff8]
     5ac: 913fe210     	add	x16, x16, #0xff8
     5b0: d61f0220     	br	x17
     5b4: d503201f     	nop
     5b8: d503201f     	nop
     5bc: d503201f     	nop

00000000000005c0 <__libc_start_main@plt>:
     5c0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     5c4: f9400211     	ldr	x17, [x16]
     5c8: 91000210     	add	x16, x16, #0x0
     5cc: d61f0220     	br	x17

00000000000005d0 <__cxa_finalize@plt>:
     5d0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     5d4: f9400611     	ldr	x17, [x16, #0x8]
     5d8: 91002210     	add	x16, x16, #0x8
     5dc: d61f0220     	br	x17

00000000000005e0 <__gmon_start__@plt>:
     5e0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     5e4: f9400a11     	ldr	x17, [x16, #0x10]
     5e8: 91004210     	add	x16, x16, #0x10
     5ec: d61f0220     	br	x17

00000000000005f0 <abort@plt>:
     5f0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     5f4: f9400e11     	ldr	x17, [x16, #0x18]
     5f8: 91006210     	add	x16, x16, #0x18
     5fc: d61f0220     	br	x17

Disassembly of section .text:

0000000000000600 <_start>:
     600: d503245f     	bti	c
     604: d280001d     	mov	x29, #0x0
     608: d280001e     	mov	x30, #0x0
     60c: aa0003e5     	mov	x5, x0
     610: f94003e1     	ldr	x1, [sp]
     614: 910023e2     	add	x2, sp, #0x8
     618: 910003e6     	mov	x6, sp
     61c: f00000e0     	adrp	x0, 0x1f000 <__FRAME_END__+0x1e774>
     620: f947ec00     	ldr	x0, [x0, #0xfd8]
     624: d2800003     	mov	x3, #0x0
     628: d2800004     	mov	x4, #0x0
     62c: 97ffffe5     	bl	0x5c0 <__libc_start_main@plt>
     630: 97fffff0     	bl	0x5f0 <abort@plt>

0000000000000634 <call_weak_fn>:
     634: f00000e0     	adrp	x0, 0x1f000 <__FRAME_END__+0x1e774>
     638: f947e800     	ldr	x0, [x0, #0xfd0]
     63c: b4000040     	cbz	x0, 0x644 <call_weak_fn+0x10>
     640: 17ffffe8     	b	0x5e0 <__gmon_start__@plt>
     644: d65f03c0     	ret
     648: d503201f     	nop
     64c: d503201f     	nop
     650: d503201f     	nop
     654: d503201f     	nop
     658: d503201f     	nop
     65c: d503201f     	nop

0000000000000660 <deregister_tm_clones>:
     660: 90000100     	adrp	x0, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     664: 9100c000     	add	x0, x0, #0x30
     668: 90000101     	adrp	x1, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     66c: 9100c021     	add	x1, x1, #0x30
     670: eb00003f     	cmp	x1, x0
     674: 540000c0     	b.eq	0x68c <deregister_tm_clones+0x2c>
     678: f00000e1     	adrp	x1, 0x1f000 <__FRAME_END__+0x1e774>
     67c: f947e021     	ldr	x1, [x1, #0xfc0]
     680: b4000061     	cbz	x1, 0x68c <deregister_tm_clones+0x2c>
     684: aa0103f0     	mov	x16, x1
     688: d61f0200     	br	x16
     68c: d65f03c0     	ret

0000000000000690 <register_tm_clones>:
     690: 90000100     	adrp	x0, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     694: 9100c000     	add	x0, x0, #0x30
     698: 90000101     	adrp	x1, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     69c: 9100c021     	add	x1, x1, #0x30
     6a0: cb000021     	sub	x1, x1, x0
     6a4: d37ffc22     	lsr	x2, x1, #63
     6a8: 8b810c41     	add	x1, x2, x1, asr #3
     6ac: 9341fc21     	asr	x1, x1, #1
     6b0: b40000c1     	cbz	x1, 0x6c8 <register_tm_clones+0x38>
     6b4: f00000e2     	adrp	x2, 0x1f000 <__FRAME_END__+0x1e774>
     6b8: f947f042     	ldr	x2, [x2, #0xfe0]
     6bc: b4000062     	cbz	x2, 0x6c8 <register_tm_clones+0x38>
     6c0: aa0203f0     	mov	x16, x2
     6c4: d61f0200     	br	x16
     6c8: d65f03c0     	ret

00000000000006cc <__do_global_dtors_aux>:
     6cc: d503233f     	paciasp
     6d0: a9be7bfd     	stp	x29, x30, [sp, #-0x20]!
     6d4: 910003fd     	mov	x29, sp
     6d8: f9000bf3     	str	x19, [sp, #0x10]
     6dc: 90000113     	adrp	x19, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     6e0: 3940c260     	ldrb	w0, [x19, #0x30]
     6e4: 37000140     	tbnz	w0, #0x0, 0x70c <__do_global_dtors_aux+0x40>
     6e8: f00000e0     	adrp	x0, 0x1f000 <__FRAME_END__+0x1e774>
     6ec: f947e400     	ldr	x0, [x0, #0xfc8]
     6f0: b4000080     	cbz	x0, 0x700 <__do_global_dtors_aux+0x34>
     6f4: 90000100     	adrp	x0, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x48>
     6f8: f9401400     	ldr	x0, [x0, #0x28]
     6fc: 97ffffb5     	bl	0x5d0 <__cxa_finalize@plt>
     700: 97ffffd8     	bl	0x660 <deregister_tm_clones>
     704: 52800020     	mov	w0, #0x1
     708: 3900c260     	strb	w0, [x19, #0x30]
     70c: f9400bf3     	ldr	x19, [sp, #0x10]
     710: a8c27bfd     	ldp	x29, x30, [sp], #0x20
     714: d50323bf     	autiasp
     718: d65f03c0     	ret
     71c: d503201f     	nop

0000000000000720 <frame_dummy>:
     720: d503245f     	bti	c
     724: 17ffffdb     	b	0x690 <register_tm_clones>

0000000000000728 <main>:
     728: d100c3ff     	sub	sp, sp, #0x30
     72c: b9002fff     	str	wzr, [sp, #0x2c]
     730: b9002bff     	str	wzr, [sp, #0x28]
     734: 14000001     	b	0x738 <main+0x10>
     738: b9402be8     	ldr	w8, [sp, #0x28]
     73c: 71002908     	subs	w8, w8, #0xa
     740: 1a9fb7e8     	cset	w8, ge
     744: 37000148     	tbnz	w8, #0x0, 0x76c <main+0x44>
     748: 14000001     	b	0x74c <main+0x24>
     74c: b9402be8     	ldr	w8, [sp, #0x28]
     750: b9802bea     	ldrsw	x10, [sp, #0x28]
     754: 910003e9     	mov	x9, sp
     758: b82a7928     	str	w8, [x9, x10, lsl #2]
     75c: b9402be8     	ldr	w8, [sp, #0x28]
     760: 11000508     	add	w8, w8, #0x1
     764: b9002be8     	str	w8, [sp, #0x28]
     768: 17fffff4     	b	0x738 <main+0x10>
     76c: 2a1f03e0     	mov	w0, wzr
     770: 9100c3ff     	add	sp, sp, #0x30
     774: d65f03c0     	ret

Disassembly of section .fini:

0000000000000778 <_fini>:
     778: d503233f     	paciasp
     77c: a9bf7bfd     	stp	x29, x30, [sp, #-0x10]!
     780: 910003fd     	mov	x29, sp

0000000000000784 <$x>:
     784: a8c17bfd     	ldp	x29, x30, [sp], #0x10
     788: d50323bf     	autiasp
     78c: d65f03c0     	ret
