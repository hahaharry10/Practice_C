/* This file is used to explore whether the order in which variables in the
 * stack are declared reduces the amount of memory usage.
 *
 * The idea first came form the observations outlined in structPadding.c
 *
 * There was a lot of exploration required to make sense of this and the main
 * two sources are:
 *     1. System V Application Binary Interface
 *        AMD64 Architecture Processor Supplement
 *        (With LP64 and ILP32 Programming Models)
 *        Version 1.0
 *
 *     2. Procedure Call Standard for the Arm®
 *        64-bit Architecture (AArch64)
 *
 * Found at:
 *     1. https://gitlab.com/x86-psABIs/x86-64-ABI/
 *     2. https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst
 *
 * - System V ABI is used for the x86 architecture.
 * - Aarch64 ABI is used for the aarch64 architecture.
 *
 * Both the aarch64 and the System V implements a stack with the following
 * properties:
 *     - 16-byte aligned.
 *          ~ When the stack grows, the stack pointer (SP) is always aligned
 *              to the 16-byte boundary.
 *     - Downward growing.
 *          ~ Memory is assigned in descending order (from the highest memory
 *              address to the lowest address).
 *
 * My System: Apple M1 Pro
 *
 * When I compile using:
 *     $ gcc -fstack-usage -Os stackVariableOrder.c -o stackVariableOrder
 * 
 * The following stack usage file (.su) is created:
 * "
 * stackVariableOrder.c:27:6:func1	32	static
 * stackVariableOrder.c:45:6:func2	48	static
 * stackVariableOrder.c:61:5:main	16	static
 * "
 *
 * Showing a 16byte difference in stack usage between func1 and func2.
 *
 * Code output:
 * "
 * int a: 0xffffd9f1b4dc
 * int b: 0xffffd9f1b4d8
 * int c: 0xffffd9f1b4d4
 * char d: 0xffffd9f1b4d3
 * char e: 0xffffd9f1b4d2
 * char f: 0xffffd9f1b4d1
 * 
 * char a: 0xffffd9f1b4df
 * int b: 0xffffd9f1b4d8
 * char c: 0xffffd9f1b4d7
 * int d: 0xffffd9f1b4d0
 * char e: 0xffffd9f1b4cf
 * int f: 0xffffd9f1b4c8
 * "
 *
 * Showing that variables are assigned in order of declaration to memory
 * in ascending order.
 *
 * The reason the order of declaration is influences stack usage is due
 * to padding. First of all, func1 has no padding, and func2 has a total
 * of 9 bytes of padding (feel free to do the math yourself).
 *
 * As the stack grows downwards but local variables are assigned in
 * ascending order, when a function is called the stack must grow 
 * in multiples of 16 (to maintain alignment) while also having enough
 * free memory to hold all the data. As func2 has the extra 9 bytes of
 * padding, there may only be a small amount of extra memory required
 * to store the variables, but the SP must still jump to the next 
 * 16byte aligned memory space (and the extra 7 bytes would be padded).
 *
 * This means that even though there is a 9 byte difference in memory,
 * there is a 16byte difference in stack usage.
 *
 * NOTE: This difference is only noticed when using gcc. clang makes
 * both functions 48 bytes.
 *
 * So in conclusion the order in which variables are declared can
 * affect memory usage, but factors like compiler and system architecture
 * may influence whether it does make a difference. If memory optimisations
 * like these are that important to you then it is best you investigate
 * memory assignment on your own system.
 *
 */

#include <stdio.h>

void func1() {
    int a;
    int b;
    int c;

    char d;
    char e;
    char f;

    fprintf(stdout, "int a: %p\n", (void *) &a);
    fprintf(stdout, "int b: %p\n", (void *) &b);
    fprintf(stdout, "int c: %p\n", (void *) &c);

    fprintf(stdout, "char d: %p\n", (void *) &d);
    fprintf(stdout, "char e: %p\n", (void *) &e);
    fprintf(stdout, "char f: %p\n", (void *) &f);
}

void func2() {
    char a;
    int b;
    char c;
    int d;
    char e;
    int f;

    fprintf(stdout, "char a: %p\n", (void *) &a);
    fprintf(stdout, "int b: %p\n", (void *) &b);
    fprintf(stdout, "char c: %p\n", (void *) &c);
    fprintf(stdout, "int d: %p\n", (void *) &d);
    fprintf(stdout, "char e: %p\n", (void *) &e);
    fprintf(stdout, "int f: %p\n", (void *) &f);
}

int main(void) {
    func1();
    fprintf(stdout, "\n");
    func2();
    return 0;
}
