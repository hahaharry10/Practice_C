
RHSincrement.o:	file format elf64-littleaarch64

Sections:
Idx Name            Size     VMA              Type
  0                 00000000 0000000000000000 
  1 .strtab         00000078 0000000000000000 
  2 .text           00000054 0000000000000000 TEXT
  3 .comment        00000025 0000000000000000 
  4 .note.GNU-stack 00000000 0000000000000000 
  5 .eh_frame       00000030 0000000000000000 DATA
  6 .rela.eh_frame  00000018 0000000000000000 
  7 .llvm_addrsig   00000000 0000000000000000 
  8 .symtab         000000a8 0000000000000000 

Disassembly of section .text:

0000000000000000 <RHSincrement>:
       0: d10043ff     	sub	sp, sp, #0x10
       4: f90007e0     	str	x0, [sp, #0x8]
       8: b90007ff     	str	wzr, [sp, #0x4]
       c: 14000001     	b	0x10 <RHSincrement+0x10>
      10: b94007e8     	ldr	w8, [sp, #0x4]
      14: 5290d409     	mov	w9, #0x86a0
      18: 72a00029     	movk	w9, #0x1, lsl #16
      1c: 6b090108     	subs	w8, w8, w9
      20: 1a9fb7e8     	cset	w8, ge
      24: 37000128     	tbnz	w8, #0x0, 0x48 <RHSincrement+0x48>
      28: 14000001     	b	0x2c <RHSincrement+0x2c>
      2c: b94007e8     	ldr	w8, [sp, #0x4]
      30: 11000509     	add	w9, w8, #0x1
      34: b90007e9     	str	w9, [sp, #0x4]
      38: f94007e9     	ldr	x9, [sp, #0x8]
      3c: b98007ea     	ldrsw	x10, [sp, #0x4]
      40: b82a7928     	str	w8, [x9, x10, lsl #2]
      44: 17fffff3     	b	0x10 <RHSincrement+0x10>
      48: 2a1f03e0     	mov	w0, wzr
      4c: 910043ff     	add	sp, sp, #0x10
      50: d65f03c0     	ret
