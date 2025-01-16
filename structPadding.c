/* This is an exploration in the memory alignment and padding involved in
 * structs. I believed that padding was done for alignment, and that if 
 * `char c` and `int i` where members of a structure (in that order) then
 * there would be a 3 byte gap between c and i to make sure i is aligned
 * to 4 bytes (and as a result the struct would be aligned to 8 bytes).
 * But if i was places before c then there would be no need for padding
 * as i and c would be aligned appropriately and the struct would be
 * aligned to 4 bytes.
 *
 * After Running code, and further research:
 *
 * Compilation:
 * ```
 * $ clang -std=c89 -o structPadding structPadding.c
 * ```
 *
 * Output:
 * ```
 * Structure Sizes:
 *         Char first: 8
 *         Int first: 8
 * Addresses:
 *         Preceeding Char: 0xffffedbe008b
 *         Char first: 0xffffedbe0080
 *                 Member 1: 0xffffedbe0080 (char)
 *                 Member 2: 0xffffedbe0084 (int)
 *         Preceeding Char: 0xffffedbe007f
 *         Int first: 0xffffedbe0074
 *                 Member 1: 0xffffedbe0074 (int)
 *                 Member 2: 0xffffedbe0078 (char)
 * ```
 *
 * So after running the code, I found the size of both structs are 8 bytes
 * and that the padding is equal. So the padding is not changed no matter
 * the order of the members. This is because the stack (at least on my
 * machine) grows downwards, this means that the first declared variable
 * (c1 at address `0xffffedbe008b`) has the highest memory address and
 * proceeding variables are assigned to the next highest available memory
 * address.
 *
 * So when the first address is assigned to `c1` it is given the highest
 * available address (which is aligned to 1 so it can just fit into the
 * highest available address). Then when `chf` is declared (size of 8 bytes)
 * the compiler needs to assign an address that is the next highest address
 * containing 8 free bytes that is also aligned to (a multiple of) 8. The
 * compiler cannot assign the variable to the next available 8-byte-aligned
 * address (which is `0xffffedbe0088`) as the there is only 3 bytes available.
 * So the next address that has 8 available bytes and is 8 byte aligned is
 * `0xffffedbe0080` which is what chf is assigned to.
 *
 * The next variable, `c2`, is a char and is 1-byte-aligned and can just slot
 * in after `chf`, and is therefore assigned in `0xffffedbe007f`. The
 * interesting thing about `intf` is that the memory address is not divisible
 * by 8, an the compiler still leaves a 3 byte gap between the end of `intf`
 * and `c2`. A quick google search attributes to the malalignment to
 * compiler optimisations but I do not and a confident answer to this one yet.
 *
 * So if I was to summarise the answers:
 *      - No matter the order of the contents of THIS struct, the struct has a
 *      size that is a multiple of the size of the largest datatype.
 *      - In C an objects alignment and size are synonymous. An objects size
 *      equates to its alignment. This is done to ensure each member of the
 *      struct is correctly aligned and so that in an array of the object,
 *      each element is corectly aligned. Therefore the padding at the end of
 *      the struct ensures that the alignment of subsequent objects is
 *      correct.
 * 
 * So at this stage I have 2 questions:
 * 1) If I have a struct like `intFirst`, and that has only 5 bytes and I fill
 * the stack with variables so that there is a 5byte difference between the 
 * next available byte and the next 8byte aligned memory space, does the 
 * variable get stored in that address or in the next address that is 8-byte-
 * aligned with 8 available bytes? I doubt it since the size is treated as
 * 8 bytes, but why doesn't the system separate size and alignment and have
 * the struct of size 5 bytes but align it to an 8 byte boundary? This way
 * arrays would be aligned appropriately (with the 3-byte pad in between) but
 * any other variables can use this wasted space. And don't answer with
 * "because memory is accessed as `root address + i * sizeof(dtype)` as this
 * implementation could be changed to `root address + i * alignmentof(dtype)`.
 *
 * 2) If variables are assigned memory in the order of declaration, and large
 * variables skip memory to reach the next valid address, Would I be able to
 * occupy less space through declaring these variables in a different order?
 *
 * Stay tuned and lets find out...
 */

#include <stdio.h>

typedef struct {
    char c;
    int i;
} charFirst;

typedef struct {
    int i;
    char c;
} intFirst;

int main(void) {
    int i;
    char c1;
    charFirst chf;
    char c2[5];
    intFirst intf;

    fprintf(stdout, "Structure Sizes:\n");
    fprintf(stdout, "\tChar first: %lu\n\tInt first: %lu\n", sizeof(chf), sizeof(intf));

    fprintf(stdout, "Addresses:\n");
    fprintf(stdout, "\tPreceeding Char: %p\n", (void *) &c1);
    fprintf(stdout, "\tChar first: %p\n\t\tMember 1: %p (char)\n\t\tMember 2: %p (int)\n", (void *) &chf, (void *) &chf.c, (void *) &chf.i);
    for( i = 0; i < 5; i++ ) {
        fprintf(stdout, "\tchar[%i]: %p\n", i, (void *) &c2[i]);
    }
    fprintf(stdout, "\tInt first: %p\n\t\tMember 1: %p (int)\n\t\tMember 2: %p (char)\n", (void *) &intf, (void *) &intf.i, (void *) &intf.c);

    return 0;
}
