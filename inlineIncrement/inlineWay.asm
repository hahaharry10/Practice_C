
inlineWay.o:	file format elf64-littleaarch64

Sections:
Idx Name            Size     VMA              Type
  0                 00000000 0000000000000000 
  1 .strtab         00000072 0000000000000000 
  2 .text           00000058 0000000000000000 TEXT
  3 .comment        00000025 0000000000000000 
  4 .note.GNU-stack 00000000 0000000000000000 
  5 .eh_frame       00000030 0000000000000000 DATA
  6 .rela.eh_frame  00000018 0000000000000000 
  7 .llvm_addrsig   00000000 0000000000000000 
  8 .symtab         000000a8 0000000000000000 

Disassembly of section .text:

0000000000000000 <inlineWay>:
       0: d10043ff     	sub	sp, sp, #0x10
       4: f90007e0     	str	x0, [sp, #0x8]
       8: b90007ff     	str	wzr, [sp, #0x4]
       c: 14000001     	b	0x10 <inlineWay+0x10>
      10: b94007e8     	ldr	w8, [sp, #0x4]
      14: 5290d409     	mov	w9, #0x86a0
      18: 72a00029     	movk	w9, #0x1, lsl #16
      1c: 6b090108     	subs	w8, w8, w9
      20: 1a9fb7e8     	cset	w8, ge
      24: 37000148     	tbnz	w8, #0x0, 0x4c <inlineWay+0x4c>
      28: 14000001     	b	0x2c <inlineWay+0x2c>
      2c: b94007e8     	ldr	w8, [sp, #0x4]
      30: f94007e9     	ldr	x9, [sp, #0x8]
      34: b98007ea     	ldrsw	x10, [sp, #0x4]
      38: 2a0a03eb     	mov	w11, w10
      3c: 1100056b     	add	w11, w11, #0x1
      40: b90007eb     	str	w11, [sp, #0x4]
      44: b82a7928     	str	w8, [x9, x10, lsl #2]
      48: 17fffff2     	b	0x10 <inlineWay+0x10>
      4c: 2a1f03e0     	mov	w0, wzr
      50: 910043ff     	add	sp, sp, #0x10
      54: d65f03c0     	ret
