# Aim
This is to look at the difference between inline variable increments.
These are all different ways to assign values from 0 to 10 in an array
in order, with a while loop:

The three methods are:
```C
int arr[10];
while( i < 10 ) {
    arr[i] = i; i++; // The standard way.
    arr[i++] = i; // The inline way.
    arr[i] = i++; // The incorrect way.
}
```

We are going to look at the different assembly code to these applcations
for the following aims...
- The standard way:
    - Understand assembly implementations of:
        1) array indexing (`arr[i]`)
        2) incrementing (`i++`)
    - Understand the order in which an address is retrieved and assigned to.
- The inline way:
    - Understand the order in which the address is retrieved, assigned to, and incremented.
- The incorrect way:
    - At what point does the incrementation happen.

If i'm honest I can pretty much guess the answer to the abstract implementation, but I do
not know specifically the assembly commands, and structuring. From learning LLVM IR I
understand that the memory address is found, stored into a register, then the value being
assigned is loaded (either direct or immediate addressed) and then the value is assigned.

# File structure
All source files (obviously) have the `.c` file extension, and all assembly files have the
`.s` file extension, and the related files have the same name. The names match the code
snippets under the [aim](#aim). The source files are called:
- [standardWay.c](./standardWay.c)
- [inlineWay.c](./inlineWay.c)
- [incorrectWay.c](./incorrectWay.c)

### Admission of Ignorance
Before writing the code, I made initial guesses on which methods will be correct and
incorrect. I incorrectly guessed the following:
```
arr[i] = i++; // Was the correct way.
arr[i++] = i; // Was the incorrect way.
```
And named the files accordingly. When I wrote the tests I realised I was wrong. I
initially thought the memory was accessed/ loaded in chronological order, but this seems
not the case.

I have changed the names of the files to correctly identify the correct (inline) and
incorrect method.

# Compilation
The [build](./build) bash script is used to compile and produce the assembly code. The
usage is found with:
```
$ ./build -h
Usage: ./build [-clean-asm] [-clean] file_basename
	-clean-asm: Remove all assembly files.
	-clean: Remove all assmbly and executable files.
```

Where `file_basename` is the file name with the file extension omitted.

# Document Structure
It may not be the right way to write a document like this, but the document will be written
and is intended to be read in chronological order. The subsequent sections may assume
knowledge from the previous sections. So feel free to skip sections, but you may have to
read the preceeding sections anyway.

# Preamble
I am running on an aarch 64 machine, so all my this information will rely on the following resources:
- Aarch64 Procedure Call Standard (https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst)
- Learn the architecture - A64 Instruction Set Architecture (https://developer.arm.com/documentation/102374/0102)
- ARM Compiler toolchain Using the Assembler (https://developer.arm.com/documentation/dui0473/c)

Also I used ChatGPT to help me with wording some concepts.

When writing this document I am in the early stages of learning and understanding assembly
language so I will strive to produce a clear explanation of the concepts concerning this
investigation.

# Investigation:
## Brief Lesson on Assembly
To understand the difference in implementation of the different methods, we must first
understand a little about assembly. This section will provide a brief explanation on the
assembly implementation of [standardWay.c](./standardWay.c) (it is useful to learn and
thoroughly understand this source code).

To follow the assembly you can either look at [standardWay.asm](./standardWay.asm) or
to look at [main.c](./main.c) and find the label `0000000000000b4c <standardWay>:`.

### Calling the function:
In assembly there are no function calls, there are no subroutines or function calls. But
instead there is branching. Branching allows you to skip forward (and backward) to another
instruction. Branching can be done unconditionally or conditionally.

When calling a function in assembly you do not _call_ anything, you instead skip forward
to the instruction that runs the functions code and then after the function is executed you
branch back to resume execution. Look at the below flowchart, all the blocks is one 
large code chunk, where the code of each block is immediately after the previous block.

![Branch Execution Flowchat](./images/branch.png)

In the function call, the execution flow skips down to the function logic, and then when
function logic is completed, the flow skips back to the line of `main()` immediately after
the function code.

### Registers and Function Parameters:
There are 31 accessible registers (r0-r30), but some of then have special functions. These
registers can be accessed as a 64 bit register by using `xn` or a 32 bit register by using
`wn`, where `n` is the register number. The called function can modify registers 0-15
freely.

when calling a function, registers r0 to r7 are used for parameter passing, and any further
parameters are passed onto the stack.

The vast majority of operations we are going to look at uses registers. So it is important
to track when registers are being loaded to, stored to memory, and operated on as registers
are not automatically saved to memory.

### The Stack
The stack is pointed to by the stack pointer (`sp`). The stack has the following properties:
1. The Stack Pointer is always 16-byte aligned.
2. The stack grows downward (memory is assigned from the highest memory address first)

This means that for the stack to grown, the stack pointer is subtracted (grows downward) by
a multiple of 16 (to keep 16-byte alignment). The stack is used to store values for later
use (there is more stack space than register space).

## Running `main`
If you run main with:
```
$ ./main 2>log.txt
```

You get an output similar to (the times may change):
```
The Standard Way:
	PASSED: arr[i] = i
Time: 94

The inline Way:
	PASSED: arr[i] = i
Time: 353

The incorrect Way:
	FAILED: 99999 index-value pairs do not match.
Time: 114
```
After running 10 times we get the following average times:
|Algorithm:|Processor Time:|
|:--------:|--------------:|
|Standard Way|142.2|
|Inline Way|524.7|
|Incorrect Way|127.1|

NOTE: We are reading in processor time over 100000 iterations. So the differences in
processing costs is minute.

Initial Observations:
- The incorrect way is the fastest and the inline way is the slowest.
- Even though both the incorrect and inline way have an inlined incrementation, the
incorrect way is 400% quicker.
- Having two separate statements are quicker than incrementing upon memory access.

