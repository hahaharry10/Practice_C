
main:	file format elf64-littleaarch64

Sections:
Idx Name               Size     VMA              Type
  0                    00000000 0000000000000000 
  1 .interp            0000001b 0000000000000238 DATA
  2 .note.gnu.build-id 00000024 0000000000000254 
  3 .note.ABI-tag      00000020 0000000000000278 
  4 .gnu.hash          0000001c 0000000000000298 
  5 .dynsym            00000138 00000000000002b8 
  6 .dynstr            000000a9 00000000000003f0 
  7 .gnu.version       0000001a 000000000000049a 
  8 .gnu.version_r     00000030 00000000000004b8 
  9 .rela.dyn          000000f0 00000000000004e8 
 10 .rela.plt          00000090 00000000000005d8 
 11 .init              0000001c 0000000000000668 TEXT
 12 .plt               00000080 0000000000000690 TEXT
 13 .text              00000510 0000000000000740 TEXT
 14 .fini              00000018 0000000000000c50 TEXT
 15 .rodata            0000009f 0000000000000c68 DATA
 16 .eh_frame_hdr      0000005c 0000000000000d08 DATA
 17 .eh_frame          00000144 0000000000000d68 DATA
 18 .init_array        00000008 000000000001fdb8 
 19 .fini_array        00000008 000000000001fdc0 
 20 .dynamic           000001e0 000000000001fdc8 
 21 .got               00000040 000000000001ffa8 DATA
 22 .got.plt           00000048 000000000001ffe8 DATA
 23 .data              00000010 0000000000020030 DATA
 24 .bss               00000008 0000000000020040 BSS
 25 .comment           00000042 0000000000000000 
 26 .symtab            00000a38 0000000000000000 
 27 .strtab            000002ca 0000000000000000 
 28 .shstrtab          00000103 0000000000000000 

Disassembly of section .init:

0000000000000668 <_init>:
     668: d503233f     	paciasp
     66c: a9bf7bfd     	stp	x29, x30, [sp, #-0x10]!
     670: 910003fd     	mov	x29, sp
     674: 94000040     	bl	0x774 <call_weak_fn>

0000000000000678 <$x>:
     678: a8c17bfd     	ldp	x29, x30, [sp], #0x10
     67c: d50323bf     	autiasp
     680: d65f03c0     	ret

Disassembly of section .plt:

0000000000000690 <$x>:
     690: a9bf7bf0     	stp	x16, x30, [sp, #-0x10]!
     694: f00000f0     	adrp	x16, 0x1f000 <__FRAME_END__+0x1e158>
     698: f947fe11     	ldr	x17, [x16, #0xff8]
     69c: 913fe210     	add	x16, x16, #0xff8
     6a0: d61f0220     	br	x17
     6a4: d503201f     	nop
     6a8: d503201f     	nop
     6ac: d503201f     	nop

00000000000006b0 <clock@plt>:
     6b0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     6b4: f9400211     	ldr	x17, [x16]
     6b8: 91000210     	add	x16, x16, #0x0
     6bc: d61f0220     	br	x17

00000000000006c0 <__libc_start_main@plt>:
     6c0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     6c4: f9400611     	ldr	x17, [x16, #0x8]
     6c8: 91002210     	add	x16, x16, #0x8
     6cc: d61f0220     	br	x17

00000000000006d0 <__cxa_finalize@plt>:
     6d0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     6d4: f9400a11     	ldr	x17, [x16, #0x10]
     6d8: 91004210     	add	x16, x16, #0x10
     6dc: d61f0220     	br	x17

00000000000006e0 <__gmon_start__@plt>:
     6e0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     6e4: f9400e11     	ldr	x17, [x16, #0x18]
     6e8: 91006210     	add	x16, x16, #0x18
     6ec: d61f0220     	br	x17

00000000000006f0 <abort@plt>:
     6f0: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     6f4: f9401211     	ldr	x17, [x16, #0x20]
     6f8: 91008210     	add	x16, x16, #0x20
     6fc: d61f0220     	br	x17

0000000000000700 <fprintf@plt>:
     700: 90000110     	adrp	x16, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     704: f9401611     	ldr	x17, [x16, #0x28]
     708: 9100a210     	add	x16, x16, #0x28
     70c: d61f0220     	br	x17

Disassembly of section .text:

0000000000000740 <_start>:
     740: d503245f     	bti	c
     744: d280001d     	mov	x29, #0x0
     748: d280001e     	mov	x30, #0x0
     74c: aa0003e5     	mov	x5, x0
     750: f94003e1     	ldr	x1, [sp]
     754: 910023e2     	add	x2, sp, #0x8
     758: 910003e6     	mov	x6, sp
     75c: f00000e0     	adrp	x0, 0x1f000 <__FRAME_END__+0x1e158>
     760: f947ec00     	ldr	x0, [x0, #0xfd8]
     764: d2800003     	mov	x3, #0x0
     768: d2800004     	mov	x4, #0x0
     76c: 97ffffd5     	bl	0x6c0 <__libc_start_main@plt>
     770: 97ffffe0     	bl	0x6f0 <abort@plt>

0000000000000774 <call_weak_fn>:
     774: f00000e0     	adrp	x0, 0x1f000 <__FRAME_END__+0x1e158>
     778: f947e800     	ldr	x0, [x0, #0xfd0]
     77c: b4000040     	cbz	x0, 0x784 <call_weak_fn+0x10>
     780: 17ffffd8     	b	0x6e0 <__gmon_start__@plt>
     784: d65f03c0     	ret
     788: d503201f     	nop
     78c: d503201f     	nop
     790: d503201f     	nop
     794: d503201f     	nop
     798: d503201f     	nop
     79c: d503201f     	nop

00000000000007a0 <deregister_tm_clones>:
     7a0: 90000100     	adrp	x0, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     7a4: 91010000     	add	x0, x0, #0x40
     7a8: 90000101     	adrp	x1, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     7ac: 91010021     	add	x1, x1, #0x40
     7b0: eb00003f     	cmp	x1, x0
     7b4: 540000c0     	b.eq	0x7cc <deregister_tm_clones+0x2c>
     7b8: f00000e1     	adrp	x1, 0x1f000 <__FRAME_END__+0x1e158>
     7bc: f947d821     	ldr	x1, [x1, #0xfb0]
     7c0: b4000061     	cbz	x1, 0x7cc <deregister_tm_clones+0x2c>
     7c4: aa0103f0     	mov	x16, x1
     7c8: d61f0200     	br	x16
     7cc: d65f03c0     	ret

00000000000007d0 <register_tm_clones>:
     7d0: 90000100     	adrp	x0, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     7d4: 91010000     	add	x0, x0, #0x40
     7d8: 90000101     	adrp	x1, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     7dc: 91010021     	add	x1, x1, #0x40
     7e0: cb000021     	sub	x1, x1, x0
     7e4: d37ffc22     	lsr	x2, x1, #63
     7e8: 8b810c41     	add	x1, x2, x1, asr #3
     7ec: 9341fc21     	asr	x1, x1, #1
     7f0: b40000c1     	cbz	x1, 0x808 <register_tm_clones+0x38>
     7f4: f00000e2     	adrp	x2, 0x1f000 <__FRAME_END__+0x1e158>
     7f8: f947f042     	ldr	x2, [x2, #0xfe0]
     7fc: b4000062     	cbz	x2, 0x808 <register_tm_clones+0x38>
     800: aa0203f0     	mov	x16, x2
     804: d61f0200     	br	x16
     808: d65f03c0     	ret

000000000000080c <__do_global_dtors_aux>:
     80c: d503233f     	paciasp
     810: a9be7bfd     	stp	x29, x30, [sp, #-0x20]!
     814: 910003fd     	mov	x29, sp
     818: f9000bf3     	str	x19, [sp, #0x10]
     81c: 90000113     	adrp	x19, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     820: 39410260     	ldrb	w0, [x19, #0x40]
     824: 37000140     	tbnz	w0, #0x0, 0x84c <__do_global_dtors_aux+0x40>
     828: f00000e0     	adrp	x0, 0x1f000 <__FRAME_END__+0x1e158>
     82c: f947dc00     	ldr	x0, [x0, #0xfb8]
     830: b4000080     	cbz	x0, 0x840 <__do_global_dtors_aux+0x34>
     834: 90000100     	adrp	x0, 0x20000 <_GLOBAL_OFFSET_TABLE_+0x58>
     838: f9401c00     	ldr	x0, [x0, #0x38]
     83c: 97ffffa5     	bl	0x6d0 <__cxa_finalize@plt>
     840: 97ffffd8     	bl	0x7a0 <deregister_tm_clones>
     844: 52800020     	mov	w0, #0x1
     848: 39010260     	strb	w0, [x19, #0x40]
     84c: f9400bf3     	ldr	x19, [sp, #0x10]
     850: a8c27bfd     	ldp	x29, x30, [sp], #0x20
     854: d50323bf     	autiasp
     858: d65f03c0     	ret
     85c: d503201f     	nop

0000000000000860 <frame_dummy>:
     860: d503245f     	bti	c
     864: 17ffffdb     	b	0x7d0 <register_tm_clones>

0000000000000868 <check>:
     868: d10083ff     	sub	sp, sp, #0x20
     86c: a9017bfd     	stp	x29, x30, [sp, #0x10]
     870: 910043fd     	add	x29, sp, #0x10
     874: f90007e0     	str	x0, [sp, #0x8]
     878: b90007ff     	str	wzr, [sp, #0x4]
     87c: b90003ff     	str	wzr, [sp]
     880: 14000001     	b	0x884 <check+0x1c>
     884: b94003e8     	ldr	w8, [sp]
     888: 5290d409     	mov	w9, #0x86a0
     88c: 72a00029     	movk	w9, #0x1, lsl #16
     890: 6b090108     	subs	w8, w8, w9
     894: 1a9fb7e8     	cset	w8, ge
     898: 37000428     	tbnz	w8, #0x0, 0x91c <check+0xb4>
     89c: 14000001     	b	0x8a0 <check+0x38>
     8a0: f94007e8     	ldr	x8, [sp, #0x8]
     8a4: b98003e9     	ldrsw	x9, [sp]
     8a8: b8697908     	ldr	w8, [x8, x9, lsl #2]
     8ac: b94003e9     	ldr	w9, [sp]
     8b0: 6b090108     	subs	w8, w8, w9
     8b4: 1a9f17e8     	cset	w8, eq
     8b8: 37000208     	tbnz	w8, #0x0, 0x8f8 <check+0x90>
     8bc: 14000001     	b	0x8c0 <check+0x58>
     8c0: f00000e8     	adrp	x8, 0x1f000 <__FRAME_END__+0x1e158>
     8c4: f947e108     	ldr	x8, [x8, #0xfc0]
     8c8: f9400100     	ldr	x0, [x8]
     8cc: b94003e2     	ldr	w2, [sp]
     8d0: f94007e8     	ldr	x8, [sp, #0x8]
     8d4: b98003e9     	ldrsw	x9, [sp]
     8d8: b8697903     	ldr	w3, [x8, x9, lsl #2]
     8dc: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     8e0: 9131b021     	add	x1, x1, #0xc6c
     8e4: 97ffff87     	bl	0x700 <fprintf@plt>
     8e8: b94007e8     	ldr	w8, [sp, #0x4]
     8ec: 11000508     	add	w8, w8, #0x1
     8f0: b90007e8     	str	w8, [sp, #0x4]
     8f4: 14000001     	b	0x8f8 <check+0x90>
     8f8: f94007e9     	ldr	x9, [sp, #0x8]
     8fc: b98003ea     	ldrsw	x10, [sp]
     900: 2a1f03e8     	mov	w8, wzr
     904: b82a7928     	str	w8, [x9, x10, lsl #2]
     908: 14000001     	b	0x90c <check+0xa4>
     90c: b94003e8     	ldr	w8, [sp]
     910: 11000508     	add	w8, w8, #0x1
     914: b90003e8     	str	w8, [sp]
     918: 17ffffdb     	b	0x884 <check+0x1c>
     91c: b94007e8     	ldr	w8, [sp, #0x4]
     920: 71000108     	subs	w8, w8, #0x0
     924: 1a9f07e8     	cset	w8, ne
     928: 37000128     	tbnz	w8, #0x0, 0x94c <check+0xe4>
     92c: 14000001     	b	0x930 <check+0xc8>
     930: f00000e8     	adrp	x8, 0x1f000 <__FRAME_END__+0x1e158>
     934: f947e508     	ldr	x8, [x8, #0xfc8]
     938: f9400100     	ldr	x0, [x8]
     93c: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     940: 91320821     	add	x1, x1, #0xc82
     944: 97ffff6f     	bl	0x700 <fprintf@plt>
     948: 14000009     	b	0x96c <check+0x104>
     94c: f00000e8     	adrp	x8, 0x1f000 <__FRAME_END__+0x1e158>
     950: f947e508     	ldr	x8, [x8, #0xfc8]
     954: f9400100     	ldr	x0, [x8]
     958: b94007e2     	ldr	w2, [sp, #0x4]
     95c: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     960: 91325c21     	add	x1, x1, #0xc97
     964: 97ffff67     	bl	0x700 <fprintf@plt>
     968: 14000001     	b	0x96c <check+0x104>
     96c: a9417bfd     	ldp	x29, x30, [sp, #0x10]
     970: 910083ff     	add	sp, sp, #0x20
     974: d65f03c0     	ret

0000000000000978 <main>:
     978: a9be7bfd     	stp	x29, x30, [sp, #-0x20]!
     97c: f9000bfc     	str	x28, [sp, #0x10]
     980: 910003fd     	mov	x29, sp
     984: d14187ff     	sub	sp, sp, #0x61, lsl #12  // =0x61000
     988: d12b03ff     	sub	sp, sp, #0xac0
     98c: d10023a8     	sub	x8, x29, #0x8
     990: f9000fe8     	str	x8, [sp, #0x18]
     994: f00000e9     	adrp	x9, 0x1f000 <__FRAME_END__+0x1e158>
     998: f947e529     	ldr	x9, [x9, #0xfc8]
     99c: f90013e9     	str	x9, [sp, #0x20]
     9a0: b900051f     	str	wzr, [x8, #0x4]
     9a4: b900011f     	str	wzr, [x8]
     9a8: 14000001     	b	0x9ac <main+0x34>
     9ac: f9400fe8     	ldr	x8, [sp, #0x18]
     9b0: b9400108     	ldr	w8, [x8]
     9b4: 5290d409     	mov	w9, #0x86a0
     9b8: 72a00029     	movk	w9, #0x1, lsl #16
     9bc: 6b090108     	subs	w8, w8, w9
     9c0: 1a9fb7e8     	cset	w8, ge
     9c4: 370001a8     	tbnz	w8, #0x0, 0x9f8 <main+0x80>
     9c8: 14000001     	b	0x9cc <main+0x54>
     9cc: f9400fe8     	ldr	x8, [sp, #0x18]
     9d0: b980010a     	ldrsw	x10, [x8]
     9d4: 9100e3e9     	add	x9, sp, #0x38
     9d8: 2a1f03e8     	mov	w8, wzr
     9dc: b82a7928     	str	w8, [x9, x10, lsl #2]
     9e0: 14000001     	b	0x9e4 <main+0x6c>
     9e4: f9400fe9     	ldr	x9, [sp, #0x18]
     9e8: b9400128     	ldr	w8, [x9]
     9ec: 11000508     	add	w8, w8, #0x1
     9f0: b9000128     	str	w8, [x9]
     9f4: 17ffffee     	b	0x9ac <main+0x34>
     9f8: 97ffff2e     	bl	0x6b0 <clock@plt>
     9fc: f9001be0     	str	x0, [sp, #0x30]
     a00: 9100e3e0     	add	x0, sp, #0x38
     a04: f90003e0     	str	x0, [sp]
     a08: 94000051     	bl	0xb4c <standardWay>
     a0c: 97ffff29     	bl	0x6b0 <clock@plt>
     a10: f94013e8     	ldr	x8, [sp, #0x20]
     a14: f90017e0     	str	x0, [sp, #0x28]
     a18: f9400100     	ldr	x0, [x8]
     a1c: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     a20: 91331021     	add	x1, x1, #0xcc4
     a24: 97ffff37     	bl	0x700 <fprintf@plt>
     a28: f94003e0     	ldr	x0, [sp]
     a2c: 97ffff8f     	bl	0x868 <check>
     a30: f94013e8     	ldr	x8, [sp, #0x20]
     a34: f9400100     	ldr	x0, [x8]
     a38: f94017e8     	ldr	x8, [sp, #0x28]
     a3c: f9401be9     	ldr	x9, [sp, #0x30]
     a40: eb090102     	subs	x2, x8, x9
     a44: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     a48: 91335c21     	add	x1, x1, #0xcd7
     a4c: f90007e1     	str	x1, [sp, #0x8]
     a50: 97ffff2c     	bl	0x700 <fprintf@plt>
     a54: f94013e8     	ldr	x8, [sp, #0x20]
     a58: f9400100     	ldr	x0, [x8]
     a5c: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     a60: 91330821     	add	x1, x1, #0xcc2
     a64: f9000be1     	str	x1, [sp, #0x10]
     a68: 97ffff26     	bl	0x700 <fprintf@plt>
     a6c: 97ffff11     	bl	0x6b0 <clock@plt>
     a70: aa0003e8     	mov	x8, x0
     a74: f94003e0     	ldr	x0, [sp]
     a78: f9001be8     	str	x8, [sp, #0x30]
     a7c: 9400004a     	bl	0xba4 <inlineWay>
     a80: 97ffff0c     	bl	0x6b0 <clock@plt>
     a84: f94013e8     	ldr	x8, [sp, #0x20]
     a88: f90017e0     	str	x0, [sp, #0x28]
     a8c: f9400100     	ldr	x0, [x8]
     a90: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     a94: 91338821     	add	x1, x1, #0xce2
     a98: 97ffff1a     	bl	0x700 <fprintf@plt>
     a9c: f94003e0     	ldr	x0, [sp]
     aa0: 97ffff72     	bl	0x868 <check>
     aa4: f94007e1     	ldr	x1, [sp, #0x8]
     aa8: f94013e8     	ldr	x8, [sp, #0x20]
     aac: f9400100     	ldr	x0, [x8]
     ab0: f94017e8     	ldr	x8, [sp, #0x28]
     ab4: f9401be9     	ldr	x9, [sp, #0x30]
     ab8: eb090102     	subs	x2, x8, x9
     abc: 97ffff11     	bl	0x700 <fprintf@plt>
     ac0: f94013e8     	ldr	x8, [sp, #0x20]
     ac4: f9400be1     	ldr	x1, [sp, #0x10]
     ac8: f9400100     	ldr	x0, [x8]
     acc: 97ffff0d     	bl	0x700 <fprintf@plt>
     ad0: 97fffef8     	bl	0x6b0 <clock@plt>
     ad4: aa0003e8     	mov	x8, x0
     ad8: f94003e0     	ldr	x0, [sp]
     adc: f9001be8     	str	x8, [sp, #0x30]
     ae0: 94000047     	bl	0xbfc <incorrectWay>
     ae4: 97fffef3     	bl	0x6b0 <clock@plt>
     ae8: f94013e8     	ldr	x8, [sp, #0x20]
     aec: f90017e0     	str	x0, [sp, #0x28]
     af0: f9400100     	ldr	x0, [x8]
     af4: 90000001     	adrp	x1, 0x0 <stdout@GLIBC_2.17>
     af8: 9133cc21     	add	x1, x1, #0xcf3
     afc: 97ffff01     	bl	0x700 <fprintf@plt>
     b00: f94003e0     	ldr	x0, [sp]
     b04: 97ffff59     	bl	0x868 <check>
     b08: f94007e1     	ldr	x1, [sp, #0x8]
     b0c: f94013e8     	ldr	x8, [sp, #0x20]
     b10: f9400100     	ldr	x0, [x8]
     b14: f94017e8     	ldr	x8, [sp, #0x28]
     b18: f9401be9     	ldr	x9, [sp, #0x30]
     b1c: eb090102     	subs	x2, x8, x9
     b20: 97fffef8     	bl	0x700 <fprintf@plt>
     b24: f94013e8     	ldr	x8, [sp, #0x20]
     b28: f9400be1     	ldr	x1, [sp, #0x10]
     b2c: f9400100     	ldr	x0, [x8]
     b30: 97fffef4     	bl	0x700 <fprintf@plt>
     b34: 2a1f03e0     	mov	w0, wzr
     b38: 914187ff     	add	sp, sp, #0x61, lsl #12  // =0x61000
     b3c: 912b03ff     	add	sp, sp, #0xac0
     b40: f9400bfc     	ldr	x28, [sp, #0x10]
     b44: a8c27bfd     	ldp	x29, x30, [sp], #0x20
     b48: d65f03c0     	ret

0000000000000b4c <standardWay>:
     b4c: d10043ff     	sub	sp, sp, #0x10
     b50: f90007e0     	str	x0, [sp, #0x8]
     b54: b90007ff     	str	wzr, [sp, #0x4]
     b58: 14000001     	b	0xb5c <standardWay+0x10>
     b5c: b94007e8     	ldr	w8, [sp, #0x4]
     b60: 5290d409     	mov	w9, #0x86a0
     b64: 72a00029     	movk	w9, #0x1, lsl #16
     b68: 6b090108     	subs	w8, w8, w9
     b6c: 1a9fb7e8     	cset	w8, ge
     b70: 37000148     	tbnz	w8, #0x0, 0xb98 <standardWay+0x4c>
     b74: 14000001     	b	0xb78 <standardWay+0x2c>
     b78: b94007e8     	ldr	w8, [sp, #0x4]
     b7c: f94007e9     	ldr	x9, [sp, #0x8]
     b80: b98007ea     	ldrsw	x10, [sp, #0x4]
     b84: b82a7928     	str	w8, [x9, x10, lsl #2]
     b88: b94007e8     	ldr	w8, [sp, #0x4]
     b8c: 11000508     	add	w8, w8, #0x1
     b90: b90007e8     	str	w8, [sp, #0x4]
     b94: 17fffff2     	b	0xb5c <standardWay+0x10>
     b98: 2a1f03e0     	mov	w0, wzr
     b9c: 910043ff     	add	sp, sp, #0x10
     ba0: d65f03c0     	ret

0000000000000ba4 <inlineWay>:
     ba4: d10043ff     	sub	sp, sp, #0x10
     ba8: f90007e0     	str	x0, [sp, #0x8]
     bac: b90007ff     	str	wzr, [sp, #0x4]
     bb0: 14000001     	b	0xbb4 <inlineWay+0x10>
     bb4: b94007e8     	ldr	w8, [sp, #0x4]
     bb8: 5290d409     	mov	w9, #0x86a0
     bbc: 72a00029     	movk	w9, #0x1, lsl #16
     bc0: 6b090108     	subs	w8, w8, w9
     bc4: 1a9fb7e8     	cset	w8, ge
     bc8: 37000148     	tbnz	w8, #0x0, 0xbf0 <inlineWay+0x4c>
     bcc: 14000001     	b	0xbd0 <inlineWay+0x2c>
     bd0: b94007e8     	ldr	w8, [sp, #0x4]
     bd4: f94007e9     	ldr	x9, [sp, #0x8]
     bd8: b98007ea     	ldrsw	x10, [sp, #0x4]
     bdc: 2a0a03eb     	mov	w11, w10
     be0: 1100056b     	add	w11, w11, #0x1
     be4: b90007eb     	str	w11, [sp, #0x4]
     be8: b82a7928     	str	w8, [x9, x10, lsl #2]
     bec: 17fffff2     	b	0xbb4 <inlineWay+0x10>
     bf0: 2a1f03e0     	mov	w0, wzr
     bf4: 910043ff     	add	sp, sp, #0x10
     bf8: d65f03c0     	ret

0000000000000bfc <incorrectWay>:
     bfc: d10043ff     	sub	sp, sp, #0x10
     c00: f90007e0     	str	x0, [sp, #0x8]
     c04: b90007ff     	str	wzr, [sp, #0x4]
     c08: 14000001     	b	0xc0c <incorrectWay+0x10>
     c0c: b94007e8     	ldr	w8, [sp, #0x4]
     c10: 5290d409     	mov	w9, #0x86a0
     c14: 72a00029     	movk	w9, #0x1, lsl #16
     c18: 6b090108     	subs	w8, w8, w9
     c1c: 1a9fb7e8     	cset	w8, ge
     c20: 37000128     	tbnz	w8, #0x0, 0xc44 <incorrectWay+0x48>
     c24: 14000001     	b	0xc28 <incorrectWay+0x2c>
     c28: b94007e8     	ldr	w8, [sp, #0x4]
     c2c: 11000509     	add	w9, w8, #0x1
     c30: b90007e9     	str	w9, [sp, #0x4]
     c34: f94007e9     	ldr	x9, [sp, #0x8]
     c38: b98007ea     	ldrsw	x10, [sp, #0x4]
     c3c: b82a7928     	str	w8, [x9, x10, lsl #2]
     c40: 17fffff3     	b	0xc0c <incorrectWay+0x10>
     c44: 2a1f03e0     	mov	w0, wzr
     c48: 910043ff     	add	sp, sp, #0x10
     c4c: d65f03c0     	ret

Disassembly of section .fini:

0000000000000c50 <_fini>:
     c50: d503233f     	paciasp
     c54: a9bf7bfd     	stp	x29, x30, [sp, #-0x10]!
     c58: 910003fd     	mov	x29, sp

0000000000000c5c <$x>:
     c5c: a8c17bfd     	ldp	x29, x30, [sp], #0x10
     c60: d50323bf     	autiasp
     c64: d65f03c0     	ret
