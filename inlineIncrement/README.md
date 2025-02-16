# Aim
This is to look at the difference between inline variable increments. These are
all different ways to assign values from 0 to 10 in an array in order, with a
while loop:

The three methods are:
```C
int arr[10];
while( i < 10 ) {
    arr[i] = i; i++; // The correct way.
    arr[i++] = i; // The LHS increment way.
    arr[i] = i++; // The RHS increment way.
}
```

By the end of the document, you will understand the assembly generated from the
correct way, and understand the differnce in execution time between the three
methods, and understand why the LHS and RHS increment ways result in undefined
behaviour.

# Contents
- [Aim](#aim)
- [Contents](#contents)
- [Preamble](#preamble)
    - [File Structure](#file-structure)
    - [Compilation](#compilation)
    - [Admission of Ignorance](#admission-of-ignorance)
- [Understanding The Assembly](#understanding-the-assembly)
    - [Brief Lesson on Assembly](#brief-lesson-on-assembly)
        - [Function Calls](#function-calls)
        - [Registers](#registers)
        - [The Stack](#the-stack)
        - [Addressing](#addressing)
    - [Assembly for the Correct Way](#assembly-for-the-correct-way)
        - [Lessons](#lessons)
        - [Final Remarks](#final-remarks)
    - [Sources](#sources)
- [Running `main`](#running-main)
- [Correct vs LHSincrement](#correct-vs-lhsincrement)
    - [Initial Questions](#initial-questions)
    - [Basic Blocks](#basic-blocks)
    - [Instruction Level Parallelism (ILP)](#instruction-level-parallelism-ilp)
- [The Incorrect Way](#the-incorrect-way)
- [Undefined Behaviour](#undefined-behaviour)
    - [Undefined Behaviour vs Unspecified Behaviour](#undefined-behaviour-vs-unspecified-behaviour)
    - [Sequence Points](#sequence-points)
    - [Why the Inline Code is Undefined](#why-the-inline-code-is-undefined)
        - [Using Different Compilers](#using-different-compilers)

# Preamble
It may not be the right way to write a document like this, but the document
will be written and is intended to be read in chronological order. The
subsequent sections may assume knowledge from the previous sections. So feel
free to skip sections, but you may have to read the preceeding sections anyway.

Disclaimer: I am learning as I write the document, and try correct all my
mistakes but I may miss some. Please contact me or create an issue regarding
any mistakes.

## File Structure
All source files (obviously) have the `.c` file extension, and all assembly
files have the `.asm` file extension, and the related files have the same name.
The names match the code snippets under the [aim](#aim). The source files are
called:
- [correctWay.c](./correctWay.c)
    - The only correct method.
- [LHSincrement.c](./LHSincrement.c)
    - The increment is on the left hand side of the assignment.
- [RHSincrement.c](./RHSincrement.c)
    - The increment is on the right hand side of the assignment.

Both the LHS and RHS increments may be grouped under the term inline method, or
inline way. This is because the increment occurs inline with the array
assignment.

## Compilation
The [build](./build) bash script is used to compile and produce the assembly
code. The usage is found with:
```
$ ./build -h
Usage: ./build [-clean-asm] [-clean] file_basename
	-clean-asm: Remove all assembly files.
	-clean: Remove all assmbly and executable files.
	-gcc: Use GNU compiler (LLVM is default).
	-std=c99: Use C99 standard (C89 is default).
```

Where `file_basename` is the file name with the file extension omitted.

## Admission of Ignorance
Before writing this document I initially presumed that writing the assignment
and the increment in the same statement was a valid piece of code, however I
was wrong. Turns out having a variable being modified and accessed outside of
the expression determining the new value is undefined behaviour (see
[undefined behaviour](./README.md#undefined-behaviour)).

I wrote a substantial amount until I realised this so if there are any
inconsistencies then the original file basenames were:
|Current Basename|Original Basename|
|:--------------:|:---------------:|
|correctWay|standardWay|
|LHSincrement|inlineWay|
|RHSincrement|incorrectWay|

The reason for this is because I was using the LLVM compiler, which compiles
[LHSincrement.c](./LHSincrement.c) to executes as intended. However upon
learning that it is actually undefined behaviour I changed the file names to
match this.

# Understanding the Assembly
To understand the difference in implementation of the different methods, we
must first understand a little about assembly. This section will provide a
brief explanation on the assembly implementation of
[correctWay.c](./correctWay.c) (it is useful to learn and thoroughly
understand this source code).

To follow the assembly you can either look at
[correctWay.asm](./correctWay.asm) or to look at [main.asm](./main.asm) and
find the label `0000000000000b4c <correctWay>:`. The code snippets are
extracted from the individual assembly files, so the instruction labels will be
different in the snippets to [main.asm](./main.asm).

## Brief Lesson on Assembly
### Function Calls
In assembly there are no function calls, there are no subroutines or functions.
But instead there is branching. Branching allows you to skip forward (and
backward) to another instruction. Branching can be done unconditionally or
conditionally.

When calling a function in assembly you do not _call_ anything, you instead
skip forward to the instruction that runs the functions code and then after the
function is executed you branch back to resume execution. Look at the below
flowchart, all the blocks is one large code chunk, where the code of each block
is immediately after the previous block.

![Branch Execution Flowchat](./images/branch.png)

In the function call, the execution flow skips down to the function logic, and
then when function logic is completed, the flow skips back to the line of
`main()` immediately after the function code.

### Registers
There are 31 accessible registers (r0-r30), but some of then have special
functions. These registers can be accessed as a 64 bit register by using `xn`
or a 32 bit register by using `wn`, where `n` is the register number. The
called function can modify registers 0-15 freely.

When storing, the data being stored dependsd on the register being accessed.
Storing `x0` into memory would save all 64bits whereas storing `w0` would only
store 32 bits.

when calling a function, registers r0 to r7 are used for parameter passing, and
any further parameters are passed onto the stack.

The vast majority of operations we are going to look at uses registers. So it
is important to track when registers are being loaded to, stored to memory, and
operated on as registers are not automatically saved to memory.

There are two Zero Registers (`wxr` and `xzr`) which always reads 0 no matter
what is stored onto it.

### The Stack
The stack is pointed to by the stack pointer (`sp`). The stack has the
following properties:
1. The Stack Pointer is always 16-byte aligned.
2. The stack grows downward (memory is assigned from the highest memory address
first).

This means that for the stack to grown, the stack pointer is subtracted (grows
downward) by a multiple of 16 (to keep 16-byte alignment).

### Addressing
Although registers are the most used operand in commands, there are other ways
to address data:
- Immediate addressing: Specify the constant being used. Denoted by `#`.
- Register addressing: Specify the register.
- Direct Addressing: Specify the memory address.

The memory Address will frequently be accessed using 'Pre-indexed addressing'
which is in the form `[addr, op2]`, which references the address `addr+op2`
(you will see this when accessing stack memory).

## Assembly for the Correct Way
Take a look at [correctWay.asm](./correctWay.asm). I am going to explain the
instructions in chunks, but in each code snippets, the comments (prepended with
`;`) will give a brief desripion of the line.

Note: _TAS_ = The Above Snippet

```asm
b4c: d10043ff     	sub	sp, sp, #0x10   ; Subtrack stack pointer by 16 (remember alignmen)
b50: f90007e0     	str	x0, [sp, #0x8]  ; store the value of x0 (param 1) into sp+8
b54: b90007ff     	str	wzr, [sp, #0x4] ; Zero 4bytes starting from sp+4
```
The above snippet grows the stack by 16 bytes, stores the first argument into
sp+8. Since sp+4 is a 4byte and is assigned to 0, we can gather that sp+4 is
the address of variable `i`, from here onwards the comments will use the name
`i` as oppose to address `sp+4`, and variable `arr` as oppose to address `sp+8`
.

```asm
b58: 14000001     	b	0xb5c <correctWay+0x10>                 ; Jump to the next instruction
b5c: b94007e8     	ldr	w8, [sp, #0x4]                          ; w8 = i
b60: 5290d409     	mov	w9, #0x86a0                             ; w9 = 0x86a0
b64: 72a00029     	movk	w9, #0x1, lsl #16                   ; w9 = w9 OR (0x1 << 16)
b68: 6b090108     	subs	w8, w8, w9                          ; w8 = w8 - w9
b6c: 1a9fb7e8     	cset	w8, ge                              ; w8 = (w8 >= 0)
b70: 37000148     	tbnz	w8, #0x0, 0xb98 <correctWay+0x4c>
```

TSA is the logic for the condition in the while loop. It gets the value of
`i` and stores it inot `w8`, then loads the boundary, 100000, into `w9` and
uses a subtraction and the resulting ALU flags to test if `w8 >= w9`. `tbnz`
gets the 0th bit of w8, and branches to instruction `0xb98` if that bit is non-
zero. If the bit is non-zero then the program branches to the code after the
while loop.

Assigning `w9` to 100000 requires 2 steps because the immediate addressed value
of `mov` can be at most 16 bits and the value being assigned is `0x0186a0` (17
bits). Therefore we use 2 statements:
- `mov` to assign the lower 16 bits (0x86a0) to `w9`.
- `movk` to left shift the constant `1` 16 times and bitwise `OR` the value to
the current value of `w9` (`0x86a0 OR 0x10000 = 0x186a0 = 0d100000`).

```asm
b74: 14000001     	b	0xb78 <correctWay+0x2c>     ; Branch to the next instruction.
b78: b94007e8     	ldr	w8, [sp, #0x4]              ; w8 = i
b7c: f94007e9     	ldr	x9, [sp, #0x8]              ; x9 = arr
b80: b98007ea     	ldrsw	x10, [sp, #0x4]         ; x10 = (64bit) w8
b84: b82a7928     	str	w8, [x9, x10, lsl #2]       ; x9[x10<<2] = w8
b88: b94007e8     	ldr	w8, [sp, #0x4]              ; w8 = i
b8c: 11000508     	add	w8, w8, #0x1                ; w8 = w8 + 1
b90: b90007e8     	str	w8, [sp, #0x4]              ; i = w8
b94: 17fffff2     	b	0xb5c <correctWay+0x10>
```

Before we delve into TSA, lets remind ourselves about the parameter stored in
`sp+8`. This array is an array of integers (32 bits each), and offsetting is
in steps of one byte, so each element starts every 4 bytes from the base
address. Therefore to get the i<sup>th</sup> element from base address `sp`,
you would use `sp+(i*4)`, or the equivalent `sp+(i<<2)`. I did not find a
reason in the documentation behind the casting of `w8` to 64 bits, but I would
assume that it is to allow a greater range in representable values, reducing
the chance of overflow.

TSA handles the loops body and gets the `i`<sup>th</sup> integer value of `arr`
and assigns it to `i`, and then increments `i`. The branch jumps back to the
series of instructions that handle the loops condition.

```asm
b98: 2a1f03e0     	mov	w0, wzr         ; zero register w0
b9c: 910043ff     	add	sp, sp, #0x10   ; Shrink the stack
ba0: d65f03c0     	ret
```

TSA zero's `w0` as that would be the returned value of the function, and then
shrinks the stack back to its original size. Then the `ret` command
unconditionally branches back to the next instruction (pointed to by the LR).
This is not seen in these snippets but this function is branched to using the
`bl` command, which branches to the destination instruction while storing the 
next instruction in the Link Register `lr` (which is how the program knows
where to branch back with `ret`).

### Lessons:
The aims above focussed on understanding two incrementing and memory access.
Before we finish this section let's focus on these:

Memory is accessed from a base address and an offset. The base address in an
array would be the pointer to the array (`arr`). The offset is in steps of one
byte, so to access and integer array (an integer is 4-bytes) you would offset
in multiples of 4, bit shift leftward twice. Given that the base address
(`arr`) is stored in register `x9`, register `x10` holds the element index
(`i`), and `w8` holds the value you are assigning (`i`), it makes sense how
    `str	w8, [x9, x10, lsl #2]`
works. It is the equivalent of the C code `((char) arr)+(i<<2) = i`.

Variable increments are handled in a more clear way. The structure is simply:
1. Load variable from memory into a register.
2. Increment register value.
3. Store result back into memory.
This is shown in these lines:
```
ldr	w8, [sp, #0x4]  ; load value from memory into a register.
add	w8, w8, #0x1    ; Add register value to 1.
str	w8, [sp, #0x4]  ; Store register value back into memory.
```

### Final Remarks
Now we should have somewhat of an understanding on the correlation between C
code and the assembly. Especially we should be able to identify the assembly
implementations of the key parts of the C code (assignment and increment).
Being familiar with these will help with the next sections.

## Sources:
- Aarch64 Procedure Call Standard,
https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst
- Learn the architecture - A64 Instruction Set Architecture,
https://developer.arm.com/documentation/102374/0102
- ARM Compiler toolchain Using the Assembler,
https://developer.arm.com/documentation/dui0473/c

# Running `main`
If you run main with:
```
$ ./main 2>log.txt
```

You get an output similar to (the times may change):
```
The Correct Way:
	PASSED: arr[i] = i
Time: 165

arr[var++] = var:
	PASSED: arr[i] = i
Time: 605

arr[var] = var++:
	FAILED: 99999 index-value pairs do not match.
Time: 180
```
After running 10 times we get the following average times:
|Algorithm:|Processor Time:|
|:--------:|--------------:|
|Standard Way|142.2|
|Inline Way|524.7|
|Incorrect Way|127.1|

NOTE: We are reading in processor time over 100000 iterations, So the
differences in processing costs is minute.

Initial Observations:
- The incorrect way is the fastest and the inline way is the slowest.
- Even though both the inline ways have an inlined incrementation, the RHS
inline way is 400% quicker than the LHS inline way.
- Having two separate statements are quicker than incrementing upon memory
access.

# Correct vs LHSincrement:
To start looking where the difference in execution time comes from, let's look
at the difference in the assembly. Look at [correctWay.asm](./correctWay.asm)
and [LHSincrement.asm](./LHSincrement.asm). As the function parameters,
initialisations, and `while` conditions are identical, most of the assembly is
the same, apart from the following:

<table>
    <tr>
        <th><a href=correctWay.asm>correctWay.asm</a></th>
        <th><a href=LHSincrement.asm>LHSincrement.asm</a></th>
    </tr>
    <tr>
        <td>
<pre>
38: b82a7928     	str	w8, [x9, x10, lsl #2]
3c: b94007e8     	ldr	w8, [sp, #0x4]
40: 11000508     	add	w8, w8, #0x1
44: b90007e8     	str	w8, [sp, #0x4]
</pre>
        </td>
        <td>
<pre>
38: 2a0a03eb     	mov	w11, w10
3c: 1100056b     	add	w11, w11, #0x1
40: b90007eb     	str	w11, [sp, #0x4]
44: b82a7928     	str	w8, [x9, x10, lsl #2]
</pre>
        </td>
    </tr>
</table>

Reminder: The registers are assigned as follows:
- `w8`: The original value of `i`.
- `x9`: The value of `arr`.
- `x10`: the value of `i` casted to 64-bits.

[LHSincrement.asm](./LHSincrement.asm) retrieves the least significant 32 bits
of the 64-bit word (i.e. casts the now 64-bit value back to 32 bits and stores
it in `w11`), increments the value by one, and stores the value back into the
stack (updating `i`). Finally the original value of `i` is assigned to the
appropriate location of `arr`.

[correctWay.asm](./correctWay.asm) stores the value of `i` into the
appropriate location of `arr`, loads `i` into `w8`, increments it by one and
then stores it back onto the stack (updating `i`).

## Initial Questions
My first questions are:
1. Why are there redundant branching?
    - Instructions `28` and `c` are unnecessary.
    - Answer: [Basic Blocks](./README.md#basic-blocks)
2. In [correctWay.asm](./correctWay.asm) Why load `i` into `w8` again?
    - Probably done by the compiler automatically as a result of splitting the
    code into basic blocks.
3. Why is [correctWay.asm](./correctWay.asm) quicker than than
[LHSincrement.asm](./LHSincrement.asm) when the standard way contains more
stack memory operations?
    - Isn't accessing the stack much slower than accessing registers?
    - The standard way accesses the stack thrice (two `str` operations
    and one `ldr` operation) but the inline way accesses the stack twice (two
    `str` operations).
    - Answer:
    [Instruction Level Parallelism](./README.md#instruction-level-parallelism-pll)

## Basic Blocks
A basic block is a straight line block of code with no branches in except at
the entry, and no branches out except at the exit. The compiler splits the code
into basic blocks and uses branching to control flow between the blocks. The
compiler naturally ends the block with a branch to the start of the next block
even if the next block is immediately following.

Sources:
- Basic Blocks, [wikipedia](https://en.wikipedia.org/wiki/Basic_block)
(https://en.wikipedia.org/wiki/Basic_block)
- Control Flow Graph,
[wikipedia](https://en.wikipedia.org/wiki/Control-flow_graph)
(https://en.wikipedia.org/wiki/Control-flow_graph) 

## Instruction Level Parallelism (ILP)
Instruction Level Parallelism (ILP) describes the processors concurrent
execution of instructions. In order for instructions to be parallelised, they
must have no data dependencies (the instruction must not depend on data being
modified by the previous instructions).

First look at the two instructions in [correctWay.asm](./correctWay.asm):
```asm
38: b82a7928     	str	w8, [x9, x10, lsl #2]
3c: b94007e8     	ldr	w8, [sp, #0x4]
```
The writing to memory of instruction `38` is slow as it takes a long time to
send the value of `w8` to memory. However once the value of `w8` has been sent,
the register can be used, even if the memory write has not finished. Therefore
isntruction `3c` can begin execution before the completion of instruciton `38`.

The following instructions, `40` and `44`, cannot be parallelised as they rely
on the value of register `w8` which is being modified by the previous
instruction, therefore they must wait for the previous instruciton to execute
completely.

Now look at the instructions in [LHSincrement.asm](./LHSincrement.asm):
```asm
38: 2a0a03eb     	mov	w11, w10
3c: 1100056b     	add	w11, w11, #0x1
40: b90007eb     	str	w11, [sp, #0x4]
44: b82a7928     	str	w8, [x9, x10, lsl #2]
```

Instructions `38`, `3c`, and `40` all access register `w11`, meaning they
cannot be executed in parallel. However write instructions `40` and `44` are
able to be executed in parallel since there are no data dependencies.

However, the command `str	w8, [x9, x10, lsl #2]` is quite expensive, having
an offset addition calculation and a bit shift, this combined with the write to
memory is a time consuming task. In the standard way this instruction is near
the start of the block, allowing the proceeding instructions to be executed
in parallel. In the inline way this instruction is at the end of the block,
with no proceeding instructions, so the program may be idle until completion.

Note: I have not yet found conclusive proof that instruction level parallelism
is the reason for the difference in execution time, however I am confident that
it is a key factor.

Sources:
- Instruction-level Parallelism,
[wikipedia](https://en.wikipedia.org/wiki/Instruction-level_parallelism)
(https://en.wikipedia.org/wiki/Instruction-level_parallelism)
- AArch64 latency / throughput benchmark report,
[ocxtal/insn_bench_aarch64](https://github.com/ocxtal/insn_bench_aarch64/blob/master/results/apple_m1_firestorm.md) 
(https://github.com/ocxtal/insn_bench_aarch64/blob/master/results/apple_m1_firestorm.md)
- Apple Silicon CPU Optimization Guide

# RHS Inline Way:
We have looked at [correctWay.asm](./correctWay.asm) and
[RHSincrement.asm](./RHSincrement.asm) (the two source codes that execute
correctly) and provided possible explanations into the differences in execution
times. Now we need to discuss why [RHSincrement.asm](./RHSincrement.asm) is the
quickest out of the three.

# Undefined Behaviour
To understand why `arr[var] = var++` and `arr[var++] = var` is undefined
behaviour we must first understand two concepts:
- Undefined Behaviour and Unspecified Behaviour
- Sequence Points

## Undefined Behaviour vs Unspecified Behaviour
The [ISO C standard](https://www.iso.org/obp/ui/en/#iso:std:iso-iec:9899:ed-5:v1:en:term:3.30)
defines undefined behaviour as the following:

    "behavior, upon use of a nonportable or erroneous program construct or of
    erroneous data, for which this document imposes no requirements"

For context the ISO defines the standard C behaviour, all the standards - c89,
c99, c11, etc. - specify behaviours of the language. Undefined behaviour is
therefore behaviour that does not have to conform to the rules, and therefore
can behave in any way, no matter how dangerous. Furthermore due to the lack of
regulation in undefined behaviour, different compilers and systems may behave
differently.

The [ISO C standard](https://www.iso.org/obp/ui/en/#iso:std:iso-iec:9899:ed-5:v1:en:term:3.30)
defines unspecified behaviour as the following:

    "behavior, that results from the use of an unspecified value, or other
    behavior upon which this document provides two or more possibilities and
    imposes no further requirements on which is chosen in any instance"

This differs from undefined behaviour as unspecified behaviour has a selection
of possible outcomes, whereas there is no way to know how undefined behaviour
will act.

Note: The above definitions are from the C24 standard, although are identical
to the C89 standard the programs were compiled with.

## Sequence Points:
The [C89 standard](https://port70.net/~nsz/c/c89/c89-draft.html) defines a
sequence point as a point where all previous executions are complete and no
future executions have started. This concept is important as it allows you to
understand at what point operations are carried out.

Sequence points according to the C89 standard define sequence points as being
placed:
- Between the operands in `&&` and `||` operations. The first operand is
evaluated first. Side note:
    - If the first operand in `&&` is zero, the second operand is not
    evaluated.
    - If the first operand in `||` is non-zero, the second operand is not
    evaluated.
- After the conditional statement in the ternary operator, `?:`. The condition
is evaluated, then the control sequence is reached, then the appropriate
expression is evaluated depending on the conditions result.
- The comma separator. The left hand side is evaluated as a `void` expression,
a sequence point occurs, then the right hand side is evaluated with a return
type and value.
- The end of a full expression. A full expression is an expression that is not
part of another expression. A full expressions is:
    - An initialiser.
    - The controlling expression of a selection statement (condition of a
    conditional).
    - An expression in an expression statement.
    - The controlling expression of a `while` or `do` statement.
    - The three expressions in a `for` statement.
    - An expression in a `return` statement.
    
In between sequence points, a value shall only be modified once by the
evaluation of an expression, and all other accesses to that value must be used
to determine the result of that expression. More simply, in a statement a value
can be modified once and any other accesses to that variable must be for the
purpose of evaluating that expression.

Some sources seem to describe pre-increment as inducing a sequence point, but
in the C89 standard, it explicitly states `i = ++i + 1` as undefined.

Sources:
- The C89 Draft, [port70](https://port70.net/~nsz/c/c89/c89-draft.html)

## Why the Inline Code is Undefined
Look at the two statements:
```
arr[var++] = var;
arr[var] = var++;
```

The standard specifies that sequence points are placed after a full expression.
In this case both line of code is an expression and does not contain a sequence
point until the end of the statement. This means the statement is operating
between sequence points. Although the variable `var` is being modified only
once, `var` is also being read to determine the index of `arr` to access, which
breaks the rule that all accesses of a mofified variable must be part of the
expression of which the variables value is determined. Therefore the code
is not working within the standard and is by definition of undefined behaviour.

Although the idea of undefined behaviour is considered scary, in this situation
the most probable evaluation of the expression is one of the following:
- `arr[var] = var; var++;`
- `arr[var+1] = var; var++;`
- `arr[var] = var+1; var++;`

This is not scary, the behaviour still varies between compilers and machines,
furthermore there is no guarrentee that the memory address being
unintentionally modified is not needed else where.

### Using Different Compilers:
If we look at the usage of [build](./build) (see
[here](./README.md#compilation)) we see that we are able to compile with the
C99 standard and with the GNU compiler, `gcc`. This subsection discusses the
execution of the code with these variations.

Compiling with different standards produce the same output on both compilers,
there may be different code being produced but that is beyond the scope of this
section.

The array assignments for the different compilers are summerised below:
|Source File|LLVM Behaviour|GNU Behaviour|
|:----------|:------------:|:-----------:|
|[correctWay.c](./correctWay.c)| All correct | All correct |
|[LHSincrement.c](./LHSincrement.c)| Correct | All incorrect |
|[RHSincrement.c](./RHSincrement.c)| All incorrect | All incorrect apart from `arr[0]`|

This is a clear example displaying how code execution varies between compiler. 
This shows the unpredictability of undefined behaviour, and the importance of
testing, you may have code running fine on your machine, but as soon as a
different compiler is being used, results may be vastly different.


