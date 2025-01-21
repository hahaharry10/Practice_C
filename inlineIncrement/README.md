# Aim
This is to look at the difference between inline variable increments.
These are all different ways to assign values from 0 to 10 in an array
in order, with a while loop:

The three methods are:
```C
int arr[10];
while( i < 10 ) {
    arr[i] = i; i++; // The standard way.
    arr[i] = i++; // The inline way.
    arr[i++] = i; // The incorrect way.
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

# Compilation
The [build](./build) bash script is used to compile and produce the assembly code. The
usage is as follows:
```
$ ./build file_basename
```

Where `file_basename` is the file name with the file extension omitted.

# Document Structure
It may not be the right way to write a document like this, but the document will be written
and is intended to be read in chronological order. The subsequent sections may assume
knowledge from the previous sections. So feel free to skip sections but you may have to
read the preceeding sections anyway.

# Let's get started
## The Standard Way:
This section relates to [standardWay.c](./standardWay.c) and [standardWay.s](./standardWay.s).
